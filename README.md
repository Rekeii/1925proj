
# 1925 Bookstore

A C++ project with CRUD features and  a GUI using electron.js through the use of node.js and CouchDB as a backend.

## a lil documentation


- [CouchDB](https://docs.couchdb.org/en/stable/)
- [Node.js](https://nodejs.org/api/addons.html)
- [Electron.js](https://www.electronjs.org/docs/latest)


### File Tree



```markdown
├── include
│   ├── Cashier.h
│   ├── Database.h
│   ├── Inventory.h
│   ├── Product.h
│   ├── Report.h
│   ├── User.h
├── node_modules
│   ├── ...
├── renderer
│   ├── index.html
│   ├── renderer.js
├── src
│   ├── binding.cpp
│   ├── Database.cpp
│   ├── Inventory.cpp
│   ├── Product.cpp
│   ├── Report.cpp
│   ├── User.cpp
├── binding.gyp
├── main.js
├── package.json
├── package-lock.json
└── styles.css
```

- **include** - header files
- **node_modules** - stuff downloaded from dependencies listed in package lock and i think is also where our custom add-on gets put in *(to connect C++ and GUI, electron.js, we create an addon in for node.js. Implemented in src/binding.cpp)*
- **renderer** - contains the gui in HTML. Here we can call every function we created in binding.cpp. 
- **src** - contains all the implementation files.
- **binding.cpp** - for our custom napi addon, this addon we create using c++ will connect our existing c++ code and our gui, electron.js.
- **binding.gyp** -  contains all the list of source cpp files and lists all the stuff it needs to run it.
- **main.js** - electron.js stuff, how it creates the application window.
- **package.json** - electron.js stuff again, talks about the application.

(**P.S.** *everything here is temporary, you may change everything in src and include. You may change all implementation and header files.*)



