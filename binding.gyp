{
    "targets": [
      {
        "target_name": "node-uv",
        "sources": [ "node-uv.cc" ],
        "include_dirs" : [
          "<!(node -e \"require('nan')\")"
        ]
      }
    ]
  }
