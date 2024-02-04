import 'package:cached_network_image/cached_network_image.dart';
import 'package:flutter/material.dart';
import 'package:flutter_application_2/bus/im_event_bus.dart';
import 'package:flutter_application_2/commone/gloab.dart';
import 'package:flutter_application_2/models/ec_conversation.dart';
import 'package:flutter_application_2/models/ec_conversation_item.dart';
import 'package:flutter_application_2/models/ec_message.dart';
import 'package:flutter_application_2/pages/base_page.dart';

class ConversationListPage extends BasePage {
  const ConversationListPage({Key? key}) : super(key: key);

  @override
  State<ConversationListPage> createState() => _ConversationListPageState();
}

class _ConversationListPageState extends BasePageState<ConversationListPage> {
  List<ECConversationItem>? conversationList;
  @override
  void initState() {
    super.initState();
    addListener();
    loadConversations();
  }

  void addListener() {
    ECIMMessageEvent.eventBus.on<ECMessage>().listen((msg) {
      loadConversations();
    });
  }

  void loadConversations() async {
    conversationList ??= <ECConversationItem>[];

    Global.dbConfig?.selectConversation().then((value) {
      conversationList = [];
      // 查询所有会话与会话的最新消息
      value?.forEach((element) async {
        var ret = await Global.dbConfig
            ?.queueConversationAndLastMsg(element.cid ?? 0);
        ECConversationItem item = ECConversationItem(
            conversation: ret?.conversation, lastMessage: ret?.msg);
        conversationList?.add(item);
      });
      // 刷新
      setState(() {});
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
      itemCount: conversationList?.length ?? 0,
      itemBuilder: (context, index) {
        ECConversation? converstation = conversationList?[index].conversation;
        ECMessage? msg = conversationList?[index].lastMessage;
        return ConversationCell(
          conversation: converstation,
          lastMessage: msg,
        );
      },
    );
  }
}

class ConversationCell extends StatelessWidget {
  final ECConversation? conversation;
  final ECMessage? lastMessage;

  const ConversationCell(
      {super.key, required this.conversation, this.lastMessage});

  @override
  Widget build(BuildContext context) {
    return Container(
      height: 70,
      padding: const EdgeInsets.symmetric(vertical: 0, horizontal: 15),
      child: Row(
        crossAxisAlignment: CrossAxisAlignment.center,
        children: [
          Container(
            height: 50,
            width: 50,
            decoration: BoxDecoration(
              borderRadius: BorderRadius.circular(25),
              color: const Color(0xFFE5E7FF),
            ),
            child: ClipOval(
              child: CachedNetworkImage(
                imageUrl: conversation?.avatar ?? "",
                placeholder: (context, url) =>
                    const CircularProgressIndicator(),
                errorWidget: (context, url, error) => const Icon(Icons.error),
              ),
            ),
          ),
          Expanded(
              child: Container(
            padding: const EdgeInsets.only(left: 10),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Text(
                      conversation?.name ?? "",
                      style: const TextStyle(
                        color: Color(0xFF050505),
                        fontSize: 16,
                      ),
                    ),
                    Text(
                      "${lastMessage?.timestamp}",
                      style: const TextStyle(
                        color: Color(0xFF929292),
                        fontSize: 14,
                      ),
                    ),
                  ],
                ),
                const SizedBox(
                  height: 8,
                ),
                Text(
                  lastMessage?.message ?? "",
                  style: const TextStyle(
                    color: Color(0xFF929292),
                    fontSize: 16,
                  ),
                ),
              ],
            ),
          )),
        ],
      ),
    );
  }
}
