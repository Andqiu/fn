import 'dart:convert';

class ECConversation {
  int? cid;
  String? name;
  String? avatar;

  ECConversation({this.cid, this.name, this.avatar});

  factory ECConversation.fromMap(Map<String, dynamic> data) {
    return ECConversation(
      cid: data['cid'] as int?,
      name: data['name'] as String?,
      avatar: data['avatar'] as String?,
    );
  }

  Map<String, dynamic> toMap() => {
        'cid': cid,
        'name': name,
        'avatar': avatar,
      };

  /// `dart:convert`
  ///
  /// Parses the string and returns the resulting Json object as [ECConversation].
  factory ECConversation.fromJson(String data) {
    return ECConversation.fromMap(json.decode(data) as Map<String, dynamic>);
  }

  /// `dart:convert`
  ///
  /// Converts [ECConversation] to a JSON string.
  String toJson() => json.encode(toMap());
}
