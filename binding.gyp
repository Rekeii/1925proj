{
  "targets": [
    {
      "target_name": "cpp_inventory",
      "sources": [
        "src/binding.cpp",
        "src/Product.cpp",
        "src/Inventory.cpp",
        "src/Database.cpp",
        "src/Report.cpp",
        "src/User.cpp",
      ],
      "include_dirs": [
        "include",  
        "node_modules/node-addon-api" 
      ],
      "cflags": ["-fexceptions"],
      "cflags_cc": ["-fexceptions"],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
    }
  ]
}
