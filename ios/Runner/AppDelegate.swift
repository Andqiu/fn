import UIKit
import Flutter

@UIApplicationMain
@objc class AppDelegate: FlutterAppDelegate {
    
    private static let dartChannel = "flutter.im.kumai";
    @objc
    var imChannel:FlutterMethodChannel?

  override func application(
    _ application: UIApplication,
    didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?
  ) -> Bool {
      
      let controller : FlutterViewController = window?.rootViewController as! FlutterViewController;
      imChannel = FlutterMethodChannel(name: "flutter.im.kumai", binaryMessenger: controller.binaryMessenger)
      imChannel?.setMethodCallHandler({
          (call: FlutterMethodCall, result: @escaping FlutterResult) -> Void in
          if (call.method == "login") {
              guard let argments = call.arguments as? Dictionary<String,Any> else{
                  return;
              }
              let type = (argments["type"] as? Int) ?? 1
              let ip = argments["ip"] as? String ?? ""
              let account = argments["account"] as? String ?? ""
              let pwd = argments["password"] as? String ?? ""
              IMClient.shared().login(withType: type, ip: ip, account: account, pwd: pwd)
          }else  if (call.method == "loginOut") {
              IMClient.shared().loginOut()
          }else  if (call.method == "getUserInfo") {
              let info:String = IMClient.shared().getUserInfo();
              result(info)
          } else {
              result(FlutterMethodNotImplemented)
          }}
      )
      
    GeneratedPluginRegistrant.register(with: self)
    return super.application(application, didFinishLaunchingWithOptions: launchOptions)
      
  }
}

