import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';

class TabPage extends StatefulWidget {
  final Widget child;
  const TabPage({super.key, required this.child});

  @override
  State<TabPage> createState() => _TabPageState();
}

class _TabPageState extends State<TabPage> {
  int currentIndex = 0;
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: widget.child,
      bottomNavigationBar: BottomNavigationBar(
        currentIndex: currentIndex,
        onTap: (value) {
          switch (value) {
            case 0:
              GoRouter.of(context).go('/home');
            case 1:
              GoRouter.of(context).go('/user');
            case 2:
              GoRouter.of(context).go('/setting');
          }
          setState(() {
            currentIndex = value;
          });
        },
        items: const <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.home),
            label: 'Home',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.search),
            label: 'Search',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.settings),
            label: 'Settings',
          ),
        ],
      ),
    );
  }
}
