import 'package:flutter/material.dart';
import 'package:flutter_application_2/pages/base_page.dart';
import 'package:flutter_application_2/pages/home_page.dart';

class DetailPage extends BasePage {
  final ItemCallBack? callBack;
  const DetailPage({super.key, this.callBack});

  @override
  State<DetailPage> createState() => _DetailPageState();
}

class _DetailPageState extends BasePageState<DetailPage> {
  @override
  AppBar? buildAppBar(BuildContext context) {
    return AppBar(
      title: const Text("Detail"),
    );
  }

  @override
  Widget? buildBody(BuildContext context) {
    String name = widget.callBack?.itemData?.name ?? "";
    return Center(
      child: Column(
        children: [
          Text(name),
          TextButton(
              onPressed: () {
                setState(() {
                  widget.callBack?.itemData?.name = "$name 被改变";
                  Function()? fuc = widget.callBack?.changeCallBack;
                  fuc != null ? fuc() : null;
                });
              },
              child: const Text("change"))
        ],
      ),
    );
  }
}