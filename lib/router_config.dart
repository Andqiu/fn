import 'package:flutter/material.dart';
import 'package:flutter_application_2/detail_page.dart';
import 'package:flutter_application_2/home_page.dart';
import 'package:flutter_application_2/setting_page.dart';
import 'package:flutter_application_2/tab_page.dart';
import 'package:flutter_application_2/user_page.dart';
import 'package:go_router/go_router.dart';

final router = GoRouter(initialLocation: "/home", routes: <RouteBase>[
  ShellRoute(
    routes: [
      GoRoute(
        path: "/home",
        pageBuilder: (context, state) =>
            FadeTransitionPage(key: state.pageKey, child: const HomePage()),
      ),
      GoRoute(
          path: "/user",
          pageBuilder: (context, state) =>
              FadeTransitionPage(key: state.pageKey, child: const UserPage())),
      GoRoute(
          path: "/setting",
          pageBuilder: (context, state) => FadeTransitionPage(
              key: state.pageKey, child: const SettingPage())),
    ],
    builder: (context, state, child) {
      return TabPage(child: child);
    },
  ),
  GoRoute(
    path: "/detail",
    builder: (context, state) => const DetailPage(),
  )
]);

/// A page that fades in an out.
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
