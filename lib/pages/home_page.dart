import 'package:flutter/material.dart';
import 'package:flutter_application_2/pages/base_page.dart';
import 'package:go_router/go_router.dart';

class HomePage extends BasePage {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends BasePageState<HomePage> {
  final List<ItemModel> list =
      List.generate(100, (index) => ItemModel(name: "item $index"));

  @override
  AppBar? buildAppBar(BuildContext context) {
    return AppBar(title: const Text("Home"));
  }

  @override
  Widget? buildBody(BuildContext context) {
    return ListView.separated(
        itemBuilder: (context, index) {
          ItemModel item = list[index];
          return GestureDetector(
            onTapUp: (details) {
              GoRouter.of(context).push("/detail",
                  extra: ItemCallBack(
                      itemData: item,
                      changeCallBack: () {
                        setState(() {});
                      }));
            },
            child: Container(
              color: Colors.white,
              child: ListTile(
                selectedColor: Colors.green,
                title: Text(item.name ?? ""),
              ),
            ),
          );
        },
        separatorBuilder: (context, index) {
          return Container(
            color: Colors.grey.withOpacity(0.1),
            height: 0.5,
          );
        },
        itemCount: list.length);
  }
}

class ItemModel {
  String? name;

  ItemModel({this.name});
}

class ItemCallBack {
  final ItemModel? itemData;
  final Function()? changeCallBack;
  ItemCallBack({this.itemData, this.changeCallBack});
}
