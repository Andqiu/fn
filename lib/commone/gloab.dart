// 提供五套可选主题色

import 'package:flutter/material.dart';
import 'package:flutter_application_2/commone/app_preferences.dart';
import 'package:flutter_application_2/commone/db_config.dart';
import 'package:flutter_application_2/plugin/im_plugin.dart';
import 'package:shared_preferences/shared_preferences.dart';

const _themes = <MaterialColor>[
  Colors.blue,
  Colors.cyan,
  Colors.teal,
  Colors.green,
  Colors.red,
];

class Global {
  // 可选的主题列表
  static List<MaterialColor> get themes => _themes;

  static DBConfig? dbConfig;

  static Future<void> init() async {
    // 在初始化app之前做一些事情

    // 1.初始化db
    dbConfig = DBConfig();
    await dbConfig?.createMessageTable();

    // 1.自动登录
    SharedPreferences.getInstance().then((prefs) {
      final account = prefs.getString(AppPreferences.account) ?? "";
      final pwd = prefs.getString(AppPreferences.pwd) ?? "";
      IMPlugin().login(account, pwd);
    });
  }
}
