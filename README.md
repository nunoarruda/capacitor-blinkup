# How to install this project?
1. Install [Node.js LTS](https://nodejs.org/en/)
2. Inside this project folder, run `npm install`

# How to reproduce the problem?
1. Run `npx cap sync`
2. Run `npx cap open ios`
3. Build the Xcode project (▶️)
4. Notice that the build will fail because `'BlinkUp/BlinkUp.h' file not found`

You might need to sign the Xcode project and/or choose another unique appId instead of `com.capacitor.blinkup`.

## Notes
- This plugin currently works on a Cordova project
- The BlinkUp iOS SDK was downloaded from https://developer.electricimp.com/manufacturing/sdkdocs#latest-versions
- The SDK files at `blinkup_sdk_ios_20.0.1.zip/BlinkUpSDK/BlinkUp/*` were placed at `ios/App/`
- The BlinkUp iOS SDK configuration can be found at https://github.com/SensorShare/cordova-plugin-blinkup#ios
- I did check the `Troubleshooting` guide at https://github.com/SensorShare/cordova-plugin-blinkup#troubleshooting
- I've tried many possible solutions I've found online (Stack Overflow, etc) without any success
- I did not test on Android
- For your curiosity, there is a Ionic Native wrapper for this plugin: https://ionicframework.com/docs/native/blinkup
