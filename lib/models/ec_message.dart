import 'dart:convert';

import 'package:collection/collection.dart';

class ECMessage {
  int? userId;
  String? name;
  int? type;
  int? timestamp;
  String? message;
  String? info;
  int? isOffline;
  int? msgId;
  int? riskStatus;

  ECMessage({
    this.userId,
    this.name,
    this.type,
    this.timestamp,
    this.message,
    this.info,
    this.isOffline,
    this.msgId,
    this.riskStatus,
  });

  @override
  String toString() {
    return 'EcMessage(userId: $userId, name: $name, type: $type, timestamp: $timestamp, message: $message, info: $info, isOffline: $isOffline, msgId: $msgId, riskStatus: $riskStatus)';
  }

  factory ECMessage.fromMap(Map<String, dynamic> data) => ECMessage(
        userId: data['userId'] as int?,
        name: data['name'] as String?,
        type: data['type'] as int?,
        timestamp: data['timestamp'] as int?,
        message: data['message'] as String?,
        info: data['info'] as String?,
        isOffline: data['isOffline'] as int?,
        msgId: data['msgId'] as int?,
        riskStatus: data['riskStatus'] as int?,
      );

  Map<String, dynamic> toMap() => {
        'userId': userId,
        'name': name,
        'type': type,
        'timestamp': timestamp,
        'message': message,
        'info': info,
        'isOffline': isOffline,
        'msgId': msgId,
        'riskStatus': riskStatus,
      };

  /// `dart:convert`
  ///
  /// Parses the string and returns the resulting Json object as [ECMessage].
  factory ECMessage.fromJson(String data) {
    return ECMessage.fromMap(json.decode(data) as Map<String, dynamic>);
  }

  /// `dart:convert`
  ///
  /// Converts [ECMessage] to a JSON string.
  String toJson() => json.encode(toMap());

  ECMessage copyWith({
    int? userId,
    String? name,
    int? type,
    int? timestamp,
    String? message,
    String? info,
    int? isOffline,
    int? msgId,
    int? riskStatus,
  }) {
    return ECMessage(
      userId: userId ?? this.userId,
      name: name ?? this.name,
      type: type ?? this.type,
      timestamp: timestamp ?? this.timestamp,
      message: message ?? this.message,
      info: info ?? this.info,
      isOffline: isOffline ?? this.isOffline,
      msgId: msgId ?? this.msgId,
      riskStatus: riskStatus ?? this.riskStatus,
    );
  }

  @override
  bool operator ==(Object other) {
    if (identical(other, this)) return true;
    if (other is! ECMessage) return false;
    final mapEquals = const DeepCollectionEquality().equals;
    return mapEquals(other.toMap(), toMap());
  }

  @override
  int get hashCode =>
      userId.hashCode ^
      name.hashCode ^
      type.hashCode ^
      timestamp.hashCode ^
      message.hashCode ^
      info.hashCode ^
      isOffline.hashCode ^
      msgId.hashCode ^
      riskStatus.hashCode;
}
