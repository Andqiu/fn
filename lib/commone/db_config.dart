import 'package:flutter/widgets.dart';
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

mixin ConversationTable {
  static const String _conversationTableName = "conversation";
  final String _conversationTableFields = '''
          CREATE TABLE if not exists $_conversationTableName (
               cid INTEGER PRIMARY KEY,
               name TEXT, 
               avatar TEXT,
               name TEXT
            );
          ''';
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
        String sql = "$_messageTableFields$_conversationTableFields";
        return db.execute(sql);
      },
      version: 1,
    );
  }
}
