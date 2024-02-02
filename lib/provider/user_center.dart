import 'package:flutter/material.dart';
import 'package:flutter_application_2/provider/user_info.dart';

class UserCenter extends ChangeNotifier {
  bool _isLogin = false;
  UserInfo? _userInfo;

// 是否登录
  bool get isLogin => _isLogin;
  set isLogin(bool login) {
    bool isChange = login == _isLogin;
    _isLogin = login;
    if (isChange) {
      notifyListeners();
    }
  }

// 用户信息
  UserInfo? get userInfo => _userInfo;
  set userInfo(UserInfo? userInfo) {
    _userInfo = userInfo;
    notifyListeners();
  }
}
