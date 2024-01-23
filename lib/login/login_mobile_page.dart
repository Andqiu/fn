import 'package:flutter/material.dart';
import 'package:flutter_application_2/base_page.dart';
import 'package:flutter_application_2/generated/l10n.dart';
import 'package:go_router/go_router.dart';

class LoginMobilePage extends BasePage {
  const LoginMobilePage({Key? key}) : super(key: key);

  @override
  State<LoginMobilePage> createState() => _LoginMobilePageState();
}

class _LoginMobilePageState extends BasePageState<LoginMobilePage> {
  final TextEditingController _editingController = TextEditingController();
  final FocusNode _focusNode = FocusNode(debugLabel: "Button");

  @override
  AppBar? buildAppBar(BuildContext context) {
    return AppBar(
      backgroundColor: const Color(0xFFFAFAFA),
      title: Text(
        S.current.loginMobile,
        style: const TextStyle(fontSize: 18),
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
                  borderRadius: BorderRadius.circular(28)),
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
                      controller: _editingController,
                      focusNode: _focusNode,
                      textAlignVertical: TextAlignVertical.center, // 设置垂直居中
                      decoration: InputDecoration(
                          hintText: '输入手机号码',
                          enabledBorder: const OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.transparent),
                          ),
                          focusedErrorBorder: const OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.red),
                          ),
                          focusedBorder: const OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.transparent),
                          ),
                          suffixIcon: _editingController.text.isNotEmpty
                              ? IconButton(
                                  onPressed: () {
                                    setState(() {
                                      _editingController.clear();
                                    });
                                  },
                                  icon: const Icon(Icons.clear),
                                )
                              : null),
                    )),
                  ],
                ),
              ),
            ),
          )
        ],
      ),
    );
  }
}
