import 'package:flutter/material.dart';
import 'package:flutter_application_2/custom_tab_bar.dart';
import 'package:go_router/go_router.dart';

class TabPage extends StatefulWidget {
  final String currentRoutePath;
  final Widget child;
  static const List<TabBarItemStateData> items = [
    TabBarItemStateData(
        color: Colors.black,
        name: "首页",
        imageName: "images/tab_home_A.png",
        selecteImageName: "images/tab_home_A_sel.png",
        fontSize: 11,
        selectColor: Colors.red,
        routePath: "/home"),
    TabBarItemStateData(
        color: Colors.black,
        name: "Party",
        imageName: "images/tab_live_A.png",
        selecteImageName: "images/tab_live_A_sel.png",
        fontSize: 11,
        selectColor: Colors.red,
        routePath: "/user"),
    TabBarItemStateData(
        color: Colors.black,
        name: "唱歌",
        imageName: "images/tab_songs_A.png",
        selecteImageName: "images/tab_songs_A_sel.png",
        fontSize: 11,
        selectColor: Colors.red,
        routePath: "/setting"),
    TabBarItemStateData(
        color: Colors.black,
        name: "讯息",
        imageName: "images/tab_mine_A.png",
        selecteImageName: "images/tab_mine_A_sel.png",
        fontSize: 11,
        selectColor: Colors.red,
        routePath: "/user"),
    TabBarItemStateData(
        color: Colors.black,
        name: "我的",
        imageName: "images/tab_mine_B.png",
        selecteImageName: "images/tab_mine_B_sel.png",
        fontSize: 11,
        selectColor: Colors.red,
        routePath: "/user"),
  ];
  const TabPage(
      {super.key, required this.currentRoutePath, required this.child});
  @override
  State<TabPage> createState() => _TabPageState();
}

class _TabPageState extends State<TabPage> {
  int currentIndex = 0;
  @override
  void initState() {
    super.initState();
    for (var i = 0; i < TabPage.items.length; i++) {
      TabBarItemStateData item = TabPage.items[i];
      if (item.routePath == widget.currentRoutePath) {
        setState(() {
          currentIndex = i;
        });
        break;
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: widget.child,
      bottomNavigationBar: CustomTabBar(
        items: TabPage.items,
        onTap: _onTap,
        selectedIndex: currentIndex,
      ),
    );
  }

  void _onTap(int index) {
    TabBarItemStateData item = TabPage.items[index];
    GoRouter.of(context).go(item.routePath);
    setState(() {
      currentIndex = index;
    });
  }
}
