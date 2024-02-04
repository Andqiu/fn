import 'package:flutter_application_2/models/ec_conversation.dart';
import 'package:flutter_application_2/models/ec_message.dart';

class ECConversationItem {
  ECConversation? conversation;
  ECMessage? lastMessage;
  ECConversationItem({this.conversation, this.lastMessage});
}
