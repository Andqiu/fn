import 'package:flutter/material.dart';
import 'package:flutter_application_2/pages/base_page.dart';

class PartyPage extends BasePage {
  const PartyPage({Key? key}) : super(key: key);

  @override
  State<PartyPage> createState() => _PartyPageState();
}

class _PartyPageState extends BasePageState<PartyPage> {
  @override
  AppBar? buildAppBar(BuildContext context) {
    return null;
  }

  @override
  Widget? buildBody(BuildContext context) {
    return const Center(
      child: Text("Party"),
    );
  }
}
