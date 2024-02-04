import 'package:flutter/services.dart';
import 'package:flutter_application_2/bus/im_event_bus.dart';
import 'package:flutter_application_2/commone/app_preferences.dart';
import 'package:flutter_application_2/commone/gloab.dart';
import 'package:flutter_application_2/models/ec_conversation.dart';
import 'package:flutter_application_2/models/ec_message.dart';
import 'package:flutter_application_2/provider/user_center.dart';
import 'package:flutter_application_2/provider/user_info.dart';
import 'package:flutter_application_2/router/router_config.dart';
import 'dart:io';
import 'package:flutter_application_2/apis/urls.dart';
import 'dart:convert';
import 'package:crypto/crypto.dart';
import 'package:go_router/go_router.dart';
import 'package:provider/provider.dart';
import 'package:shared_preferences/shared_preferences.dart';

abstract class NativeMethodChannel {
  final String channelKey;
  final MethodChannel channel;
  NativeMethodChannel(this.channelKey) : channel = MethodChannel(channelKey);

  Future<dynamic> callMethod(String method, [dynamic argments]) async {
    try {
      dynamic ret = await channel.invokeMethod(method, argments);
      return ret;
    } catch (e) {
      print('>>>> Error calling native method: $e');
    }
  }
}

class IMPlugin extends NativeMethodChannel {
  static IMPlugin? _instance;
  factory IMPlugin() {
    _instance ??= IMPlugin._internal();
    return _instance!;
  }

  IMPlugin._internal() : super(channeKey) {
    channel.setMethodCallHandler((call) {
      return callHandle(call);
    });
  }

  static const String channeKey = "flutter.im.kumai";

  Future<void> callHandle(MethodCall call) async {
    //
    print(">>>>> ${call.method},${call.arguments}");
    Map<Object?, Object?> dic = call.arguments;
    if (call.method == "im_onLoginSuccess") {
      String? msg = dic['msg'] as String? ?? "";
      imOnLoginSuccess(msg);
    } else if (call.method == "im_onMessage") {
      int uid = dic['userId'] as int;
      String name = dic['name'] as String? ?? "";
      int type = dic['type'] as int;
      int timestamp = dic['timestamp'] as int;
      String message = dic['message'] as String? ?? "";
      String info = dic['info'] as String? ?? "";
      int isOffline = dic['isOffline'] as int;
      int msgId = dic['msgId'] as int;
      int riskStatus = dic['riskStatus'] as int;
      imOnMessage(
          msgId: msgId,
          type: type,
          uid: uid,
          name: name,
          message: message,
          info: info,
          isOffline: isOffline == 1,
          riskStatus: riskStatus,
          timestamp: timestamp);
    }
  }

  String? _account;
  String? _pwd;

  Future<void> login(String account, String pwd) async {
    _account = account;
    _pwd = pwd;
    String url = dnsHost; // 替换为你的URL
    try {
      List<InternetAddress> addresses = await InternetAddress.lookup(url);
      if (addresses.isNotEmpty && addresses[0].rawAddress.isNotEmpty) {
        String ipAddress = addresses[0].address;
        print('>>>> IP Address for $url: $ipAddress');
        callMethod("login", {
          "ip": ipAddress,
          "type": 1,
          "account": "+886-$account",
          "password": sha1sum(pwd)
        });
      } else {
        print('>>>> Unable to resolve IP Address for $url');
      }
    } catch (e) {
      print('>>>> Error: $e');
    }
  }

  Future<void> imOnLoginSuccess(String msg) async {
    String userInfoStr = await callMethod("getUserInfo");
    UserInfo user = UserInfo.fromJson(userInfoStr);
    rootNavigatorKey.currentContext?.read<UserCenter>().userInfo = user;
    rootNavigatorKey.currentContext?.read<UserCenter>().isLogin = true;
    if (rootNavigatorKey.currentContext != null) {
      GoRouter.of(rootNavigatorKey.currentContext!).go("/home");
    }
    final prefs = await SharedPreferences.getInstance();
    await prefs.setString(AppPreferences.account, _account ?? "");
    await prefs.setString(AppPreferences.pwd, _pwd ?? "");
  }

  void imOnMessage(
      {required int msgId,
      required int type,
      required int uid,
      required String name,
      required String message,
      required String info,
      required bool isOffline,
      required int riskStatus,
      required int timestamp}) async {
    final ECMessage msgData = ECMessage(
        msgId: msgId,
        type: type,
        userId: uid,
        name: name,
        message: message,
        info: info,
        isOffline: isOffline ? 1 : 0,
        riskStatus: riskStatus,
        timestamp: timestamp);
    await Global.dbConfig?.insertMessage(msgData);
    bool? hasExit = await Global.dbConfig?.isExitConversation(uid);
    if (hasExit != true) {
      Map<String, dynamic> namDic = json.decode(info) as Map<String, dynamic>;
      ECConversation conversation = ECConversation(
          cid: uid, name: namDic['name'], avatar: namDic['avatar']);
      await Global.dbConfig?.insertConversation(conversation);
    }
    // 通过bus通知到需要消息刷新的组件中
    ECIMMessageEvent.eventBus.fire(msgData);
  }
}

String sha1sum(String password) {
  if (password.isEmpty) {
    return "";
  }
  Uint8List data = utf8.encode(password);
  Digest digest = sha1.convert(data);

  return digest.toString();
}
