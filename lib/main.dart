import 'package:flutter/material.dart';
import 'package:flutter_application_2/provider/user_center.dart';
import 'package:flutter_application_2/router_config.dart';

import 'package:flutter_localizations/flutter_localizations.dart';
import 'package:provider/provider.dart';
import 'generated/l10n.dart';

void main() {
  runApp(const EncoreApp());
}

class EncoreApp extends StatelessWidget {
  const EncoreApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    // 使用provider 保存UserCenter 全局状态
    return ChangeNotifierProvider(
      create: (context) => UserCenter(),
      // 使用AppHiddenKeyBoard 来处理全局点击空白处隐藏键盘
      child: AppHiddenKeyBoard(
        // app设置路由
        child: MaterialApp.router(
          debugShowCheckedModeBanner: false,
          theme: ThemeData(
            highlightColor: Colors.transparent,
            splashFactory: NoSplash.splashFactory, // 全局隐藏水波纹效果
            colorScheme: ColorScheme.fromSeed(
                seedColor: const Color.fromARGB(255, 203, 195, 218)),
            useMaterial3: true,
          ),
          localizationsDelegates: const [
            S.delegate,
            GlobalMaterialLocalizations.delegate,
            GlobalCupertinoLocalizations.delegate,
            GlobalWidgetsLocalizations.delegate
          ],
          supportedLocales: S.delegate.supportedLocales,
          // locale: const Locale('zh', 'TW'),
          locale: const Locale('en', 'US'),
          routerConfig: router,
        ),
      ),
    );
  }
}

class AppHiddenKeyBoard extends StatelessWidget {
  final Widget child;
  const AppHiddenKeyBoard({super.key, required this.child});

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      child: child,
      onTap: () {
        FocusScopeNode currentFocus = FocusScope.of(context);
        if (!currentFocus.hasPrimaryFocus &&
            currentFocus.focusedChild != null) {
          /// 取消焦点，相当于关闭键盘
          FocusManager.instance.primaryFocus?.unfocus();
        }
      },
    );
  }
}
