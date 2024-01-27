// DO NOT EDIT. This is code generated via package:intl/generate_localized.dart
// This is a library that provides messages for a en locale. All the
// messages from the main program should be duplicated here with the same
// function name.

// Ignore issues from commonly used lints in this file.
// ignore_for_file:unnecessary_brace_in_string_interps, unnecessary_new
// ignore_for_file:prefer_single_quotes,comment_references, directives_ordering
// ignore_for_file:annotate_overrides,prefer_generic_function_type_aliases
// ignore_for_file:unused_import, file_names, avoid_escaping_inner_quotes
// ignore_for_file:unnecessary_string_interpolations, unnecessary_string_escapes

import 'package:intl/intl.dart';
import 'package:intl/message_lookup_by_library.dart';

final messages = new MessageLookup();

typedef String MessageIfAbsent(String messageStr, List<dynamic> args);

class MessageLookup extends MessageLookupByLibrary {
  String get localeName => 'en';

  final messages = _notInlinedMessages(_notInlinedMessages);
  static Map<String, Function> _notInlinedMessages(_) => <String, Function>{
        "appProtocol":
            MessageLookupByLibrary.simpleMessage("同意《歡歌用戶服務協議》、《隱私聲明》"),
        "facebookLoginBtn":
            MessageLookupByLibrary.simpleMessage("使用Facebook登錄"),
        "forgetPwd": MessageLookupByLibrary.simpleMessage("忘记密码"),
        "googleLoginBtn": MessageLookupByLibrary.simpleMessage("使用Google登錄"),
        "inputMobilePlaceholder":
            MessageLookupByLibrary.simpleMessage("请输入手机号码"),
        "inputPwdPlaceholder": MessageLookupByLibrary.simpleMessage("请输入密码"),
        "login": MessageLookupByLibrary.simpleMessage("登录"),
        "loginMobile": MessageLookupByLibrary.simpleMessage("手机登录"),
        "loginWithOtherType": MessageLookupByLibrary.simpleMessage("或使用以下方式登入")
      };
}
