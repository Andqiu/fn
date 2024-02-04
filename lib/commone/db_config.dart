import 'package:flutter/widgets.dart';
import 'package:flutter_application_2/models/ec_conversation.dart';
import 'package:flutter_application_2/models/ec_message.dart';
import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';

const String _dbName = "app.db";

// 消息表
mixin MessageTable {
  static const String _messageTableName = "message";
  final String _messageTableFields = '''
          CREATE TABLE if not exists $_messageTableName (
               msgId INTEGER PRIMARY KEY,
               type INTEGER, 
               userId INTEGER,
               name TEXT,
               timestamp INTEGER,
               message TEXT,
               info TEXT,
               isOffline INTEGER,
               riskStatus INTEGER
            );
          ''';
  // 插入消息
  Future<void> insertMessage(ECMessage msg) async {
    final db = DBConfig.database;
    await db?.insert(
      _messageTableName,
      msg.toMap(),
      conflictAlgorithm: ConflictAlgorithm.replace,
    );
  }

  // 查询消息
  Future<List<ECMessage>?> messages() async {
    final db = DBConfig.database;

    final List<Map<String, Object?>>? maps = await db?.query(_messageTableName);
    if (maps?.isEmpty == true) {
      return null;
    }
    final maps0 = maps!;
    return List.generate(maps0.length, (i) {
      final map = maps0[i];
      return ECMessage.fromMap(map);
    });
  }
}
// 会话表
mixin ConversationTable {
  static const String _conversationTableName = "conversation";
  final String _conversationTableFields = '''
          CREATE TABLE if not exists $_conversationTableName (
               cid INTEGER PRIMARY KEY,
               name TEXT, 
               avatar TEXT
            )
          ''';

  Future<bool> isExitConversation(int conversatonId) async {
    final db = DBConfig.database;

    List<Map<String, dynamic>> result = await db!.rawQuery(
        'SELECT * from $_conversationTableName where cid=$conversatonId');

    return result.isEmpty == false;
  }

  Future<int> insertConversation(ECConversation converstation) async {
    final db = DBConfig.database;
    return db!.insert(_conversationTableName, converstation.toMap());
  }

  Future<List<ECConversation>?> selectConversation() async {
    final db = DBConfig.database;
    return db!.rawQuery('SELECT * from $_conversationTableName').then((value) {
      List<ECConversation> conversations =
          value.map((e) => ECConversation.fromMap(e)).toList();
      return conversations;
    });
  }
}

class DBConfig with MessageTable, ConversationTable {
  static Database? database;

  Future<void> createMessageTable() async {
    WidgetsFlutterBinding.ensureInitialized();
    String doc = await getDatabasesPath();
    String path = join("$doc/database/", _dbName);
    print(">>>>> db path $path");
    database = await openDatabase(
      path,
      onCreate: (db, version) {
        // return db.execute("$_messageTableFields$_conversationTableFields");
        String sql1 = _messageTableFields;
        Future create1 = db.execute(sql1);

        String sql2 = _conversationTableFields;
        Future create2 = db.execute(sql2);
        Future ret = Future.wait([create1, create2]);
        return ret;
      },
      version: 1,
    );
  }

  Future<({ECConversation? conversation, ECMessage? msg})>
      queueConversationAndLastMsg(int cid) async {
    final db = DBConfig.database;
    String sql = '''
    select
      conversation.*,
      conversation.name as cname,
      message.*
    from 
      ${ConversationTable._conversationTableName} conversation
    join
      ${MessageTable._messageTableName} message on conversation.cid = message.userId
    where
      conversation.cid = $cid
      AND message.timestamp = (
        SELECT
            MAX(timestamp)
        FROM
            ${MessageTable._messageTableName}
        WHERE
            userId = $cid
    );
    ''';
    return db!.rawQuery(sql).then((value) {
      var dic = value.first;
      ECConversation conversation = ECConversation.fromMap(dic);
      String? cName = dic["cname"] as String?;
      conversation.name = cName;
      ECMessage lastMsg = ECMessage.fromMap(dic);
      return (conversation: conversation, msg: lastMsg);
    });
  }
}
