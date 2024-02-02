import 'package:flutter/material.dart';

class BasePage extends StatefulWidget {
  const BasePage({super.key});

  @override
  State<BasePage> createState() => BasePageState();
}

class BasePageState<T extends BasePage> extends State<T> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: buildAppBar(context),
      body: Container(
        color: const Color(0xFFFAFAFA),
        child: buildBody(context),
      ),
    );
  }

  AppBar? buildAppBar(BuildContext context) {
    return AppBar(
        title: const Text(
      "Home",
      style: TextStyle(fontSize: 15),
    ));
  }

  Widget? buildBody(BuildContext context) {
    return null;
  }
}
