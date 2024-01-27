import 'package:flutter/material.dart';
import 'package:flutter_application_2/detail_page.dart';
import 'package:flutter_application_2/home_page.dart';
import 'package:flutter_application_2/login/login_mobile_page.dart';
import 'package:flutter_application_2/login/login_type_page.dart';
import 'package:flutter_application_2/provider/user_center.dart';
import 'package:flutter_application_2/setting_page.dart';
import 'package:flutter_application_2/tab_page.dart';
import 'package:flutter_application_2/user_page.dart';
import 'package:go_router/go_router.dart';
import 'package:provider/provider.dart';

final _rootNavigatorKey = GlobalKey<NavigatorState>();
final _sectionNavigatorKey = GlobalKey<NavigatorState>();

// 指定tab中的一个子路由为启动时页面
final router = GoRouter(
  navigatorKey: _rootNavigatorKey,
  initialLocation: "/home",
  routes: <RouteBase>[
    StatefulShellRoute.indexedStack(
      pageBuilder: (context, state, navigationShell) => NonTransitonPage(
          key: state.pageKey,
          child: TabPage(
              currentRoutePath: state.uri.path, child: navigationShell)),
      branches: [
        StatefulShellBranch(navigatorKey: _sectionNavigatorKey, routes: [
          GoRoute(
            path: "/home",
            builder: (context, state) => const HomePage(),
          ),
        ]),
        StatefulShellBranch(routes: [
          GoRoute(
            path: "/party",
            builder: (context, state) => const UserPage(),
          ),
        ]),
        StatefulShellBranch(routes: [
          GoRoute(
            path: "/sing",
            builder: (context, state) => const SettingPage(),
          ),
        ]),
        StatefulShellBranch(routes: [
          GoRoute(
            path: "/chat",
            builder: (context, state) => const SettingPage(),
          ),
        ]),
        StatefulShellBranch(routes: [
          GoRoute(
            path: "/userCenter",
            builder: (context, state) => const SettingPage(),
          ),
        ]),
      ],
    ),
    GoRoute(
      path: "/detail",
      builder: (context, state) {
        ItemCallBack item = state.extra as ItemCallBack;
        return DetailPage(
          callBack: item,
        );
      },
    ),
    GoRoute(
      path: "/loginType",
      pageBuilder: (context, state) => const MaterialPage(
        fullscreenDialog: true, // 从底部弹起
        child: LoginTypePage(),
      ),
      routes: <RouteBase>[
        GoRoute(
          path: "loginMobile",
          builder: (context, state) => const LoginMobilePage(),
        ),
      ],
    ),
  ],
  redirect: (context, state) {
    String path = state.uri.path;
    if (path == "/chat" || path == "/userCenter") {
      // 通过 provier 获取用户登录状态数据
      var userCenter = context.read<UserCenter>();
      if (!userCenter.isLogin) {
        // 重定向
        return "/loginType/loginMobile";
      }
    }
    return null;
  },
);

// 无过渡动画
class NonTransitonPage extends CustomTransitionPage {
  NonTransitonPage({
    required LocalKey key,
    required Widget child,
  }) : super(
            key: key,
            transitionsBuilder: (BuildContext context,
                    Animation<double> animation,
                    Animation<double> secondaryAnimation,
                    Widget child) =>
                child,
            child: child);
}

// 淡出动画
class FadeTransitionPage extends CustomTransitionPage<void> {
  /// Creates a [FadeTransitionPage].
  FadeTransitionPage({
    required LocalKey key,
    required Widget child,
  }) : super(
            key: key,
            transitionsBuilder: (BuildContext context,
                    Animation<double> animation,
                    Animation<double> secondaryAnimation,
                    Widget child) =>
                FadeTransition(
                  opacity: animation.drive(_curveTween),
                  child: child,
                ),
            child: child);

  static final CurveTween _curveTween = CurveTween(curve: Curves.easeIn);
}
