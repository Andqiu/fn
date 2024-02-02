import 'dart:convert';

class UserInfo {
  int? uid;
  bool? bindFb;
  bool? bindMobile;
  String? mobile;
  int? sex;
  String? nick;
  int? country;
  String? headImg;
  String? zone;
  String? token;
  String? sign;
  bool? newFbUser;
  int? needGuide;
  bool? hasPasswd;
  int? setPasswdPage;
  int? errorCode;
  String? errorMsg;
  int? style;

  UserInfo({
    this.uid,
    this.bindFb,
    this.bindMobile,
    this.mobile,
    this.sex,
    this.nick,
    this.country,
    this.headImg,
    this.zone,
    this.token,
    this.sign,
    this.newFbUser,
    this.needGuide,
    this.hasPasswd,
    this.setPasswdPage,
    this.errorCode,
    this.errorMsg,
    this.style,
  });

  factory UserInfo.fromMap(Map<String, dynamic> data) => UserInfo(
        uid: data['uid'] as int?,
        bindFb: data['bind_fb'] as bool?,
        bindMobile: data['bind_mobile'] as bool?,
        mobile: data['mobile'] as String?,
        sex: data['sex'] as int?,
        nick: data['nick'] as String?,
        country: data['country'] as int?,
        headImg: data['headImg'] as String?,
        zone: data['zone'] as String?,
        token: data['token'] as String?,
        sign: data['sign'] as String?,
        newFbUser: data['newFbUser'] as bool?,
        needGuide: data['need_guide'] as int?,
        hasPasswd: data['has_passwd'] as bool?,
        setPasswdPage: data['set_passwd_page'] as int?,
        errorCode: data['errorCode'] as int?,
        errorMsg: data['errorMsg'] as String?,
        style: data['style'] as int?,
      );

  Map<String, dynamic> toMap() => {
        'uid': uid,
        'bind_fb': bindFb,
        'bind_mobile': bindMobile,
        'mobile': mobile,
        'sex': sex,
        'nick': nick,
        'country': country,
        'headImg': headImg,
        'zone': zone,
        'token': token,
        'sign': sign,
        'newFbUser': newFbUser,
        'need_guide': needGuide,
        'has_passwd': hasPasswd,
        'set_passwd_page': setPasswdPage,
        'errorCode': errorCode,
        'errorMsg': errorMsg,
        'style': style,
      };

  /// `dart:convert`
  ///
  /// Parses the string and returns the resulting Json object as [UserInfo].
  factory UserInfo.fromJson(String data) {
    return UserInfo.fromMap(json.decode(data) as Map<String, dynamic>);
  }

  /// `dart:convert`
  ///
  /// Converts [UserInfo] to a JSON string.
  String toJson() => json.encode(toMap());
}
