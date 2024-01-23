import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';
import 'package:flutter_application_2/base_page.dart';
import 'package:flutter_application_2/generated/l10n.dart';
import 'package:go_router/go_router.dart';

class LoginTypePage extends BasePage {
  const LoginTypePage({Key? key}) : super(key: key);

  @override
  State<LoginTypePage> createState() => _LoginTypePageState();
}

class _LoginTypePageState extends BasePageState<LoginTypePage> {
  @override
  AppBar? buildAppBar(BuildContext context) {
    return null;
  }

  @override
  Widget? buildBody(BuildContext context) {
    return Scaffold(
      body: Column(
        children: [
          Expanded(
              child: Container(
            color: Colors.white,
            child: const Center(
                child: Image(image: AssetImage("images/welcome_logo.png"))),
          )),
          SizedBox(
            height: 298 + MediaQuery.of(context).padding.bottom,
            child: Column(
              children: [
                const SizedBox(
                  height: 15,
                ),
                Padding(
                  padding: const EdgeInsets.symmetric(horizontal: 15),
                  child: Container(
                    height: 44,
                    decoration: BoxDecoration(
                      color: Colors.white,
                      borderRadius: BorderRadius.circular(22.0), // 圆角半径
                      border: Border.all(
                        color: const Color(0xFFDEDEDE), // 边框颜色
                        width: 0.5, // 边框宽度
                      ),
                    ),
                    child: Stack(
                      children: [
                        Center(
                          child: Text(
                            S.of(context).googleLoginBtn,
                            style: const TextStyle(fontSize: 16),
                          ),
                        ),
                        const Positioned(
                          left: 12,
                          top: 0,
                          bottom: 0,
                          child: Center(
                            child:
                                Image(image: AssetImage("images/google.png")),
                          ),
                        )
                      ],
                    ),
                  ),
                ),
                const SizedBox(
                  height: 10,
                ),
                Padding(
                  padding: const EdgeInsets.symmetric(horizontal: 15),
                  child: Container(
                    height: 44,
                    decoration: BoxDecoration(
                      color: const Color(0xFF3A69FF),
                      borderRadius: BorderRadius.circular(22.0), // 圆角半径
                    ),
                    child: Stack(
                      children: [
                        Center(
                          child: Text(
                            S.of(context).googleLoginBtn,
                            style: const TextStyle(
                                color: Colors.white, fontSize: 16),
                          ),
                        ),
                        const Positioned(
                          left: 12,
                          top: 0,
                          bottom: 0,
                          child: Center(
                            child:
                                Image(image: AssetImage("images/facebook.png")),
                          ),
                        )
                      ],
                    ),
                  ),
                ),
                const SizedBox(
                  height: 24,
                ),
                Padding(
                  padding: const EdgeInsets.symmetric(horizontal: 20),
                  child: Row(
                    children: [
                      Flexible(
                        child: Container(
                          height: 0.5,
                          color: const Color(0xFFB2B2B2),
                        ),
                      ),
                      Padding(
                        padding: const EdgeInsets.symmetric(horizontal: 15),
                        child: Text(S.of(context).googleLoginBtn),
                      ),
                      Flexible(
                        child: Container(
                          height: 0.5,
                          color: const Color(0xFFB2B2B2),
                        ),
                      ),
                    ],
                  ),
                ),
                const SizedBox(
                  height: 24,
                ),
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    SizedBox(
                      width: 40,
                      height: 40,
                      child: IconButton(
                        padding: EdgeInsets.zero,
                        onPressed: () =>
                            GoRouter.of(context).push("/loginMobile"),
                        icon: Image.asset("images/login_phone.png"),
                      ),
                    ),
                    const SizedBox(
                      width: 50,
                    ),
                    SizedBox(
                      width: 40,
                      height: 40,
                      child: IconButton(
                        padding: EdgeInsets.zero,
                        onPressed: null,
                        icon: Image.asset("images/login_line.png"),
                      ),
                    ),
                  ],
                ),
                const SizedBox(
                  height: 34,
                ),
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    SizedBox(
                      width: 20,
                      height: 20,
                      child: IconButton(
                        padding: EdgeInsets.zero,
                        onPressed: null,
                        icon: Image.asset("images/check_box.png"),
                      ),
                    ),
                    RichText(
                      text: TextSpan(
                        text: S.current.appProtocol,
                        style: const TextStyle(
                          color: Color(0xFF547BA8),
                          // decoration: TextDecoration.underline,
                        ),
                        recognizer: TapGestureRecognizer(),
                      ),
                    )
                  ],
                )
              ],
            ),
          )
        ],
      ),
    );
  }
}
