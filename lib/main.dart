import 'package:flutter/material.dart';
import 'package:flutter_application_2/router_config.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp.router(
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        highlightColor: Colors.transparent,
        splashFactory: NoSplash.splashFactory, // 全局隐藏水波纹效果
        colorScheme: ColorScheme.fromSeed(
            seedColor: const Color.fromARGB(255, 203, 195, 218)),
        useMaterial3: true,
      ),
      routerConfig: router,
    );
  }
}
