import 'package:flutter/material.dart';
import 'package:flutter_application_2/detail_page.dart';
import 'package:flutter_application_2/home_page.dart';
import 'package:flutter_application_2/setting_page.dart';
import 'package:flutter_application_2/tab_page.dart';
import 'package:flutter_application_2/user_page.dart';
import 'package:go_router/go_router.dart';

final _rootNavigatorKey = GlobalKey<NavigatorState>();
final _sectionNavigatorKey = GlobalKey<NavigatorState>();

// 指定tab中的一个子路由为启动时页面
final router = GoRouter(
    navigatorKey: _rootNavigatorKey,
    initialLocation: "/home",
    routes: <RouteBase>[
      StatefulShellRoute.indexedStack(
          builder: (context, state, navigationShell) =>
              TabPage(currentRoutePath: state.uri.path, child: navigationShell),
          branches: [
            StatefulShellBranch(navigatorKey: _sectionNavigatorKey, routes: [
              GoRoute(
                path: "/home",
                builder: (context, state) => const HomePage(),
              ),
            ]),
            StatefulShellBranch(routes: [
              GoRoute(
                path: "/user",
                builder: (context, state) => const UserPage(),
              ),
            ]),
            StatefulShellBranch(routes: [
              GoRoute(
                path: "/setting",
                builder: (context, state) => const SettingPage(),
              ),
            ]),
          ]),
      GoRoute(
        path: "/detail",
        builder: (context, state) {
          ItemCallBack item = state.extra as ItemCallBack;
          return DetailPage(
            callBack: item,
          );
        },
      )
    ]);
