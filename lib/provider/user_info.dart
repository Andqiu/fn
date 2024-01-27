import 'package:flutter/material.dart';

class UserInfoModel extends ChangeNotifier {
  final int uid;
  String? name;
  String? avatar;
  int gender;
  UserInfoModel(
    this.uid, {
    this.gender = 1,
  });
}
