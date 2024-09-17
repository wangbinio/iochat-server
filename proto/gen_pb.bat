"E:\vcpkg\packages\protobuf_x64-windows\tools\protobuf\protoc.exe" --cpp_out=. "message.proto"

"E:\vcpkg\packages\protobuf_x64-windows\tools\protobuf\protoc.exe" -I="." --grpc_out="." --plugin=protoc-gen-grpc="E:\vcpkg\installed\x64-windows\tools\grpc\grpc_cpp_plugin.exe" "message.proto"
