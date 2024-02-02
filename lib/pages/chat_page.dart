import 'package:flutter/material.dart';
import 'package:flutter_application_2/bus/im_event_bus.dart';
import 'package:flutter_application_2/models/ec_message.dart';
import 'package:flutter_application_2/pages/base_page.dart';

class ChatPage extends BasePage {
  const ChatPage({Key? key}) : super(key: key);

  @override
  State<ChatPage> createState() => _ChatPageState();
}

class _ChatPageState extends BasePageState<ChatPage> {
  List<ECMessage>? messageList;
  @override
  void initState() {
    super.initState();
    ECIMMessageEvent.eventBus.on<ECMessage>().listen((msg) {
      print(msg);
      var list = messageList ??= <ECMessage>[];
      setState(() {
        list.add(msg);
      });
    });
  }

  @override
  AppBar? buildAppBar(BuildContext context) {
    return AppBar(
      title: const Text("消息"),
    );
  }

  @override
  Widget? buildBody(BuildContext context) {
    return ListView.builder(
      itemCount: messageList?.length ?? 0,
      itemBuilder: (context, index) {
        Text text = Text(messageList?[index].message ?? "");
        return text;
      },
    );
  }
}
