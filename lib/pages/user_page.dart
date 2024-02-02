import 'package:flutter/material.dart';
import 'package:flutter_application_2/pages/base_page.dart';
import 'package:flutter_application_2/provider/user_center.dart';
import 'package:provider/provider.dart';

class UserPage extends BasePage {
  const UserPage({Key? key}) : super(key: key);

  @override
  State<UserPage> createState() => _UserPageState();
}

class _UserPageState extends BasePageState<UserPage> {
  @override
  AppBar? buildAppBar(BuildContext context) {
    return AppBar(
      title: const Text("我的"),
    );
  }

  @override
  Widget? buildBody(BuildContext context) {
    var userCenter = context.read<UserCenter>();
    return Scaffold(
      body: Column(
        children: [
          Row(
            children: [
              Container(
                margin: const EdgeInsets.only(left: 15, top: 20),
                padding: EdgeInsets.zero,
                child: Container(
                  width: 50,
                  height: 50,
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(25),
                  ),
                  child: ClipOval(
                    child: Image(
                      image: NetworkImage(
                        userCenter.userInfo?.headImg ?? "",
                      ),
                    ),
                  ),
                ),
              ),
              Container(
                margin: const EdgeInsets.only(left: 8, top: 20),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      userCenter.userInfo?.nick ?? "",
                      style: const TextStyle(fontSize: 16, color: Colors.black),
                    ),
                    const SizedBox(
                      height: 5,
                    ),
                    Text(
                      "UID: ${userCenter.userInfo?.uid}",
                      style: const TextStyle(fontSize: 13, color: Colors.blue),
                    ),
                  ],
                ),
              ),
            ],
          )
        ],
      ),
    );
  }
}
