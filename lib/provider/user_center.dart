import 'package:flutter/material.dart';
import 'package:flutter_application_2/provider/user_info.dart';

class UserCenter extends ChangeNotifier {
  bool _isLogin = false;
  UserInfoModel? _userInfo;

// 是否登录
  set isLogin(bool login) {
    _isLogin = login;
    notifyListeners();
  }

  bool get isLogin => _isLogin;

// 用户信息
  set userInfo(UserInfoModel? userInfo) {
    _userInfo = userInfo;
    notifyListeners();
  }

  UserInfoModel? get userInfo => _userInfo;
}
