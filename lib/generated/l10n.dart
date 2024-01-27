// GENERATED CODE - DO NOT MODIFY BY HAND
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'intl/messages_all.dart';

// **************************************************************************
// Generator: Flutter Intl IDE plugin
// Made by Localizely
// **************************************************************************

// ignore_for_file: non_constant_identifier_names, lines_longer_than_80_chars
// ignore_for_file: join_return_with_assignment, prefer_final_in_for_each
// ignore_for_file: avoid_redundant_argument_values, avoid_escaping_inner_quotes

class S {
  S();

  static S? _current;

  static S get current {
    assert(_current != null,
        'No instance of S was loaded. Try to initialize the S delegate before accessing S.current.');
    return _current!;
  }

  static const AppLocalizationDelegate delegate = AppLocalizationDelegate();

  static Future<S> load(Locale locale) {
    final name = (locale.countryCode?.isEmpty ?? false)
        ? locale.languageCode
        : locale.toString();
    final localeName = Intl.canonicalizedLocale(name);
    return initializeMessages(localeName).then((_) {
      Intl.defaultLocale = localeName;
      final instance = S();
      S._current = instance;

      return instance;
    });
  }

  static S of(BuildContext context) {
    final instance = S.maybeOf(context);
    assert(instance != null,
        'No instance of S present in the widget tree. Did you add S.delegate in localizationsDelegates?');
    return instance!;
  }

  static S? maybeOf(BuildContext context) {
    return Localizations.of<S>(context, S);
  }

  /// `使用Google登錄`
  String get googleLoginBtn {
    return Intl.message(
      '使用Google登錄',
      name: 'googleLoginBtn',
      desc: '',
      args: [],
    );
  }

  /// `使用Facebook登錄`
  String get facebookLoginBtn {
    return Intl.message(
      '使用Facebook登錄',
      name: 'facebookLoginBtn',
      desc: '',
      args: [],
    );
  }

  /// `或使用以下方式登入`
  String get loginWithOtherType {
    return Intl.message(
      '或使用以下方式登入',
      name: 'loginWithOtherType',
      desc: '',
      args: [],
    );
  }

  /// `同意《歡歌用戶服務協議》、《隱私聲明》`
  String get appProtocol {
    return Intl.message(
      '同意《歡歌用戶服務協議》、《隱私聲明》',
      name: 'appProtocol',
      desc: '',
      args: [],
    );
  }

  /// `手机登录`
  String get loginMobile {
    return Intl.message(
      '手机登录',
      name: 'loginMobile',
      desc: '',
      args: [],
    );
  }

  /// `登录`
  String get login {
    return Intl.message(
      '登录',
      name: 'login',
      desc: '',
      args: [],
    );
  }

  /// `请输入密码`
  String get inputPwdPlaceholder {
    return Intl.message(
      '请输入密码',
      name: 'inputPwdPlaceholder',
      desc: '',
      args: [],
    );
  }

  /// `请输入手机号码`
  String get inputMobilePlaceholder {
    return Intl.message(
      '请输入手机号码',
      name: 'inputMobilePlaceholder',
      desc: '',
      args: [],
    );
  }

  /// `忘记密码`
  String get forgetPwd {
    return Intl.message(
      '忘记密码',
      name: 'forgetPwd',
      desc: '',
      args: [],
    );
  }
}

class AppLocalizationDelegate extends LocalizationsDelegate<S> {
  const AppLocalizationDelegate();

  List<Locale> get supportedLocales {
    return const <Locale>[
      Locale.fromSubtags(languageCode: 'en'),
      Locale.fromSubtags(languageCode: 'vi'),
      Locale.fromSubtags(languageCode: 'zh', countryCode: 'CN'),
      Locale.fromSubtags(languageCode: 'zh', countryCode: 'TW'),
    ];
  }

  @override
  bool isSupported(Locale locale) => _isSupported(locale);
  @override
  Future<S> load(Locale locale) => S.load(locale);
  @override
  bool shouldReload(AppLocalizationDelegate old) => false;

  bool _isSupported(Locale locale) {
    for (var supportedLocale in supportedLocales) {
      if (supportedLocale.languageCode == locale.languageCode) {
        return true;
      }
    }
    return false;
  }
}
