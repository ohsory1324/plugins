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
using flutter::EncodableMap;

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
      registrar->messenger(), "flutter.io/videoPlayer",
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
    if (method_call.method_name().compare("init") == 0) { // void
        result->Success();
    }
    else if (method_call.method_name().compare("create") == 0) { // map
        // video player 持失
        
        // EventChannel 持失 flutter.io/videoPlayer/videoEvents + id
        
        //auto &argsMap = method_call.arguments()->MapValue();
        //if (argsMap["asset"].StringValue()) {
            //argsMap["package"].StringValue()
        //}
        //else {
            //argsMap["uri"].StringValue()
            //argsMap["formatHint"].StringValue()
        //}
        //
        EncodableValue result = EncodableValue(EncodableMap{
            {EncodableValue("textureId"), EncodableValue(0)}
        })
        result->Success(&result);
    }
    else {
        // &argsMap = method_call.arguments()->MapValue();
        //argsMap["textureId"].StringValue();
        if (method_call.method_name().compare("dispose") == 0) { // void
            result->Success();
        }
        else if (method_call.method_name().compare("setLooping") == 0) { // void
            //argsMap["looping"].BoolValue();
            result->Success();
        }
        else if (method_call.method_name().compare("play") == 0) { // void
            result->Success();
        }
        else if (method_call.method_name().compare("pause") == 0) { // void
            result->Success();
        }
        else if (method_call.method_name().compare("setVolume") == 0) { // void
            //argsMap["volume"].DoubleValue();
            result->Success();
        }
        else if (method_call.method_name().compare("seekTo") == 0) { // void
            //argsMap["location"].IntValue();
            result->Success();
        }
        else if (method_call.method_name().compare("position") == 0) { // int
            result->Success();
        }
        result->NotImplemented();
    }
}  // namespace

void VideoPlayerPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  VideoPlayerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
