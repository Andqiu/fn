import 'package:flutter/material.dart';
import 'package:flutter/material.dart';

class CustomTabBar extends StatefulWidget {
  final List<TabBarItemStateData> items;
  final int selectedIndex;
  final Function(int) onTap;
  const CustomTabBar(
      {super.key,
      required this.items,
      required this.selectedIndex,
      required this.onTap});

  @override
  State<CustomTabBar> createState() => _CustomTabBarState();
}

class _CustomTabBarState extends State<CustomTabBar> {
  @override
  Widget build(BuildContext context) {
    double bottomSafeAreaHeight = MediaQuery.of(context).padding.bottom;

    return Container(
        height: 52 + bottomSafeAreaHeight,
        color: Colors.white,
        child: Column(
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: widget.items
                  .asMap()
                  .entries
                  .map((e) => Flexible(
                          child: GestureDetector(
                        onTap: () {
                          int index = e.key;
                          widget.onTap(index);
                        },
                        child: Container(
                          decoration: BoxDecoration(
                            color: Colors.white,
                            border: Border(
                              top: BorderSide(
                                  color: Colors.black.withOpacity(0.2),
                                  width: 0.5),
                            ),
                            boxShadow: const [
                              BoxShadow(
                                color: Colors.grey,
                                offset: Offset(0.0, 1.0), // 设置阴影偏移的位置
                                blurRadius: 1.0, // 设置阴影的模糊程度
                              ),
                            ],
                          ),
                          child: Center(
                            child: CustomTabBarItem(
                                stateData: e.value,
                                isSelected: widget.selectedIndex == e.key),
                          ),
                        ),
                      )))
                  .toList(),
            ),
            Container(
              height: bottomSafeAreaHeight,
              color: Colors.white,
              child: null,
            )
          ],
        ));
  }
}

class CustomTabBarItem extends StatelessWidget {
  final TabBarItemStateData stateData;
  final bool isSelected;
  const CustomTabBarItem(
      {super.key, required this.stateData, required this.isSelected});

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        Image(
            image: AssetImage(
                isSelected ? stateData.selecteImageName : stateData.imageName)),
        const SizedBox(height: 3),
        Text(
          stateData.name,
          style: TextStyle(
              color: isSelected ? stateData.selectColor : stateData.color,
              fontSize: stateData.fontSize),
        )
      ],
    );
  }
}

class TabBarItemStateData {
  final String imageName;
  final String selecteImageName;
  final String name;
  final Color color;
  final Color selectColor;
  final double fontSize;
  final String routePath;

  const TabBarItemStateData({
    required this.imageName,
    required this.selecteImageName,
    required this.name,
    required this.color,
    required this.selectColor,
    required this.fontSize,
    required this.routePath,
  });
}
