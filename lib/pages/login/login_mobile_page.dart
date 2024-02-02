import 'package:flutter/material.dart';
import 'package:flutter_application_2/pages/base_page.dart';
import 'package:flutter_application_2/generated/l10n.dart';
import 'package:flutter_application_2/plugin/im_plugin.dart';
import 'package:go_router/go_router.dart';

class LoginMobilePage extends BasePage {
  const LoginMobilePage({Key? key}) : super(key: key);

  @override
  State<LoginMobilePage> createState() => _LoginMobilePageState();
}

class _LoginMobilePageState extends BasePageState<LoginMobilePage> {
  final TextEditingController _mobileInputController = TextEditingController();
  final FocusNode _mobileFocusNode = FocusNode(debugLabel: "Button");
  final FocusNode _pwdFocusNode = FocusNode(debugLabel: "Button");

  final TextEditingController _pwdInputController = TextEditingController();

  String mobile = "";
  String pwd = "";
  bool get loginEnabled {
    return mobile.isNotEmpty && pwd.isNotEmpty;
  }

  void _login() {
    IMPlugin().login("1234567822", "123456");
  }

  @override
  void initState() {
    super.initState();
    _mobileFocusNode.addListener(() {
      if (!_mobileFocusNode.hasFocus) {
        // TextField 失去焦点时触发
        setState(() {});
      }
    });
    _pwdFocusNode.addListener(() {
      if (!_mobileFocusNode.hasFocus) {
        // TextField 失去焦点时触发
        setState(() {});
      }
    });
  }

  @override
  AppBar? buildAppBar(BuildContext context) {
    return AppBar(
      backgroundColor: const Color(0xFFFAFAFA),
      title: Text(
        S.current.loginMobile,
        style: const TextStyle(fontSize: 18),
      ),
      leading: BackButton(
        onPressed: () => GoRouter.of(context).go("/loginType"),
      ),
    );
  }

  @override
  Widget? buildBody(BuildContext context) {
    return Scaffold(
      body: Column(
        children: [
          const SizedBox(
            height: 60,
          ),
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 20),
            child: Container(
              height: 56,
              decoration: BoxDecoration(
                color: const Color(0xFFF2F2F2),
                borderRadius: BorderRadius.circular(28),
              ),
              child: Padding(
                padding: const EdgeInsets.symmetric(horizontal: 10),
                child: Row(
                  children: [
                    const TextButton(
                      onPressed: null,
                      child: Text(
                        "台湾 +886",
                        style:
                            TextStyle(color: Color(0xFF333333), fontSize: 16),
                      ),
                    ),
                    Flexible(
                      child: TextField(
                        onChanged: (value) {
                          setState(() {
                            mobile = value;
                          });
                        },
                        onEditingComplete: () {
                          setState(() {});
                        },
                        controller: _mobileInputController,
                        focusNode: _mobileFocusNode,
                        textAlignVertical: TextAlignVertical.center, // 设置垂直居中
                        decoration: InputDecoration(
                          contentPadding:
                              const EdgeInsets.only(bottom: -3), //这里是关键
                          hintText: S.current.inputMobilePlaceholder,
                          enabledBorder: const OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.transparent),
                          ),
                          focusedErrorBorder: const OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.red),
                          ),
                          focusedBorder: const OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.transparent),
                          ),
                          suffixIcon:
                              mobile.isNotEmpty && _mobileFocusNode.hasFocus
                                  ? IconButton(
                                      onPressed: () {
                                        setState(() {
                                          _mobileInputController.clear();
                                          mobile = "";
                                        });
                                      },
                                      icon: const Icon(Icons.clear),
                                    )
                                  : null,
                        ),
                      ),
                    ),
                  ],
                ),
              ),
            ),
          ),
          const SizedBox(
            height: 20,
          ),
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 20),
            child: Container(
              height: 56,
              padding: const EdgeInsets.symmetric(horizontal: 20),
              alignment: AlignmentDirectional.center,
              decoration: BoxDecoration(
                color: const Color(0xFFF2F2F2),
                borderRadius: BorderRadius.circular(28),
              ),
              child: TextField(
                obscureText: true,
                onChanged: (value) {
                  setState(() {
                    pwd = value;
                  });
                },
                focusNode: _pwdFocusNode,
                controller: _pwdInputController,
                textAlignVertical: TextAlignVertical.center, // 设置垂直居中
                decoration: InputDecoration(
                  contentPadding: const EdgeInsets.only(bottom: -3), //这里是关键
                  hintText: S.current.inputPwdPlaceholder,
                  enabledBorder: const OutlineInputBorder(
                    borderSide: BorderSide(color: Colors.transparent),
                  ),
                  focusedErrorBorder: const OutlineInputBorder(
                    borderSide: BorderSide(color: Colors.red),
                  ),
                  focusedBorder: const OutlineInputBorder(
                    borderSide: BorderSide(color: Colors.transparent),
                  ),
                  suffixIcon: pwd.isNotEmpty && _pwdFocusNode.hasFocus
                      ? IconButton(
                          onPressed: () {
                            setState(() {
                              _pwdInputController.clear();
                              setState(() {
                                pwd = "";
                              });
                            });
                          },
                          icon: const Icon(Icons.clear),
                        )
                      : null,
                ),
              ),
            ),
          ),
          Container(
            height: 56,
            margin: const EdgeInsets.fromLTRB(20, 30, 20, 0),
            alignment: AlignmentDirectional.center,
            decoration: BoxDecoration(
              color: loginEnabled ? Colors.red : const Color(0xFFF2F2F2),
              borderRadius: BorderRadius.circular(28),
            ),
            child: TextButton(
              onPressed: _login,
              child: Text(
                S.current.login,
                style: const TextStyle(fontSize: 18, color: Colors.white),
              ),
            ),
          ),
          const SizedBox(
            height: 10,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.end,
            children: [
              TextButton(
                onPressed: null,
                style: TextButton.styleFrom(
                  /// 清除左右的padding
                  padding: EdgeInsets.zero,
                  tapTargetSize: MaterialTapTargetSize.shrinkWrap,

                  /// 清除上下的padding
                  minimumSize: Size.zero,
                ),
                child: Text(
                  S.current.forgetPwd,
                  style:
                      const TextStyle(fontSize: 13, color: Color(0xFF999999)),
                ),
              ),
              const SizedBox(
                width: 20,
              ),
            ],
          ),
        ],
      ),
    );
  }
}
