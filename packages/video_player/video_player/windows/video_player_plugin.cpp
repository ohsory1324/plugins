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
#include "Player.h"

#include <shlObj.h>
#include <shlwapi.h>
#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <evr.h>

#include <codecvt>
#include <memory>
#include <sstream>
#include <string>

namespace {

using flutter::EncodableValue;
using flutter::EncodableMap;

CPlayer* g_pPlayer = NULL;

class VideoPlayerPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  virtual ~VideoPlayerPlugin();

 private:
  VideoPlayerPlugin(flutter::PluginRegistrarWindows *registrar);

  // Called when a method is called on plugin channel;
  void HandleMethodCall(
      const flutter::MethodCall<EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<EncodableValue>> result);

  flutter::PluginRegistrarWindows *registrar_;
};

// static
void VideoPlayerPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel = std::make_unique<flutter::MethodChannel<EncodableValue>>(
      registrar->messenger(), "flutter.io/videoPlayer",
      &flutter::StandardMethodCodec::GetInstance());

  // Uses new instead of make_unique due to private constructor.
  std::unique_ptr<VideoPlayerPlugin> plugin(new VideoPlayerPlugin(registrar));

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

VideoPlayerPlugin::VideoPlayerPlugin(flutter::PluginRegistrarWindows* registrar)
    : registrar_(registrar) {}

VideoPlayerPlugin::~VideoPlayerPlugin() = default;

void VideoPlayerPlugin::HandleMethodCall(
    const flutter::MethodCall<EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<EncodableValue>> result) {
    if (method_call.method_name().compare("init") == 0) { // void
        // player들 전부 dispose
        /* 
        The CPlayer destructor is also private.
        The CPlayer class implements IUnknown, so the object's lifetime is controlled through its reference count (m_nRefCount).
        To destroy the object, the application calls IUnknown::Release, not delete.
        */
        result->Success();
    }
    else if (method_call.method_name().compare("create") == 0) { // map
        // player 생성
        //HWND hwnd = GetAncestor(registrar_->GetView()->GetNativeWindow(), GA_ROOT);
        //HRESULT hresult = CPlayer::CreateInstance(hwnd, hwnd, &g_pPlayer);
        //printf("%d", hresult);
        
        // EventChannel 생성 flutter.io/videoPlayer/videoEvents + id
        auto channel = std::make_unique<flutter::MethodChannel<EncodableValue>>(
            registrar_->messenger(), "flutter.io/videoPlayer/videoEvents0",
            &flutter::StandardMethodCodec::GetInstance());
        channel->SetMethodCallHandler(
            [](const flutter::MethodCall<EncodableValue>& call,
                std::unique_ptr<flutter::MethodResult<EncodableValue>> result) {
                if (call.method_name().compare("listen") == 0) {
                    result->Success();
                }
                else if (call.method_name().compare("cancel") == 0) {
                    result->Success();
                }
                else {
                    result->NotImplemented();
                }
            });

        //비디오 이벤트 발생시 event, values, width, height를 Map형태로 넘겨야함
        //globalRegistrar->messenger()->SetMessageHandler(&channel, flutter::BinaryMessageHandler());

        //auto &argsMap = method_call.arguments()->MapValue();
        //if (argsMap["asset"].StringValue()) {
            //argsMap["package"].StringValue()
        //}
        //else {
            //argsMap["uri"].StringValue()
            //argsMap["formatHint"].StringValue()
        //}
        EncodableValue resultMap = EncodableValue(EncodableMap{
            {EncodableValue("textureId"), EncodableValue(0)}
        });
        result->Success(&resultMap);
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
}
}  // namespace

void VideoPlayerPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  VideoPlayerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
