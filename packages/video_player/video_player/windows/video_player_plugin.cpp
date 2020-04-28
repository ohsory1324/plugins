// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "video_player_plugin.h"

#include <ShlObj.h>
#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <windows.h>

#include <codecvt>
#include <memory>
#include <sstream>
#include <string>

namespace {

using flutter::EncodableValue;

class VideoPlayerPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrar *registrar);

  virtual ~VideoPlayerPlugin();

 private:
  VideoPlayerPlugin();

  // Called when a method is called on plugin channel;
  void HandleMethodCall(
      const flutter::MethodCall<EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<EncodableValue>> result);
};

// static
void VideoPlayerPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrar *registrar) {
  auto channel = std::make_unique<flutter::MethodChannel<EncodableValue>>(
      registrar->messenger(), "plugins.flutter.io/video_player",
      &flutter::StandardMethodCodec::GetInstance());

  // Uses new instead of make_unique due to private constructor.
  std::unique_ptr<VideoPlayerPlugin> plugin(new VideoPlayerPlugin());

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

VideoPlayerPlugin::VideoPlayerPlugin() = default;

VideoPlayerPlugin::~VideoPlayerPlugin() = default;

void VideoPlayerPlugin::HandleMethodCall(
    const flutter::MethodCall<EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<EncodableValue>> result) {
  // if (method_call.method_name().compare("getTemporaryDirectory") == 0) {
  //   wchar_t path_buffer[MAX_PATH];
  //   DWORD length = GetTempPath(MAX_PATH, path_buffer);
  //   if (length == 0 || length > MAX_PATH) {
  //     result->Error("Unable to get temporary path");
  //     return;
  //   }
  //   std::string result_path = StdStringFromWideChars(path_buffer);
  //   flutter::EncodableValue response(result_path);
  //   result->Success(&response);
  // } else if (method_call.method_name().compare(
  //                "getApplicationSupportDirectory") == 0) {
  //   std::string path = GetFolderPath(FOLDERID_RoamingAppData);
  //   if (path.empty()) {
  //     result->Error("Unable to get application data path");
  //     return;
  //   }
  //   // Use the executable name as the subdirectory for now.
  //   std::string exe_name = GetExecutableName();
  //   if (exe_name.empty()) {
  //     result->Error("Unable to get exe name");
  //     return;
  //   }
  //   std::ostringstream response_stream;
  //   response_stream << path << "\\" << exe_name;
  //   flutter::EncodableValue response(response_stream.str());
  //   result->Success(&response);
  // } else if (method_call.method_name().compare(
  //                "getApplicationDocumentsDirectory") == 0) {
  //   std::string path = GetFolderPath(FOLDERID_Documents);
  //   if (path.empty()) {
  //     result->Error("Unable to get documents path");
  //     return;
  //   }
  //   flutter::EncodableValue response(path);
  //   result->Success(&response);
  // } else {
  //   result->NotImplemented();
  // }
}

}  // namespace

void VideoPlayerPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  VideoPlayerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
