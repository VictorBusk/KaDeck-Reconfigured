const {app, session, protocol, shell, BrowserWindow, globalShortcut, Menu} = require('electron');
const path = require('path');

const appVersion = "3.0.1"; // VERSION_UPDATE Always change this Version Number
const requestPromise = require('minimal-request-promise');
const os = require('os');

let mainWindow = null;
let loadingWindow = null;
let serverProcess = null;
let updateWindow = null;
let errorWindow = null;
let licenseWindow = null;
let licenseActivationPrompted = false;
const headers = {
        'license':'0abdea078047xsFRxKnlZa128caI104d69b-ProfessionalEdition'
};
const options = {
    extraHeaders:"license:"+headers.license
};
const versionUrl = 'https://licenses.xeotek.io/v1/version';
const appUrl = 'http://localhost:8143';
let uID;
let lic_key, machine;
const hasJavaHome = !!process.env.JAVA_HOME;
let backendCrashed = false;
const openLoadingWindow = function(){
    loadingWindow = new BrowserWindow({
        title: 'KaDeck',
        width: 400,
        height: 290,
        frame: false,
        resizable: false,
        backgroundColor: "#009ae1",
        show:false
    });
    loadingWindow.loadFile("index.html");

    loadingWindow.on("closed", () => {
        loadingWindow = null;
    });

    loadingWindow.on("ready-to-show", ()=>{
        loadingWindow.show();
    });
};

const openErrorDialog = function(cause){
    errorWindow = new BrowserWindow({
        title: 'An error occurred!',
        width: 400,
        height: 170,
        frame: true,
        resizable: false,
        backgroundColor: "#f3f3f3",
        alwaysOnTop:true,
        icon: path.join(__dirname, 'assets/icons/icon')
    });
    errorWindow.loadFile("error.html");
    errorWindow.on("closed", () => {
        errorWindow = null;
    });
};

const verifyJava = function(){
    console.log("JAVA_HOME "+(hasJavaHome?"found.":"not found."));
    let java;

    if (hasJavaHome){
        console.log("Trying to start Java using JAVA_HOME.");
        try{
            let path = "";
            if (process.env.JAVA_HOME.toString().endsWith("bin/")){
                path = process.env.JAVA_HOME + 'java';
            }else if (process.env.JAVA_HOME.toString().endsWith("bin")){
                path = process.env.JAVA_HOME + '/java';
            }else{
                path = process.env.JAVA_HOME.toString().endsWith("/")?process.env.JAVA_HOME + 'bin/java':process.env.JAVA_HOME + '/bin/java';
            }
            java = require('child_process')
                .spawnSync(path, ["-version"]);
        }catch(e){}
        if (java && !java.error){
            return true;
        }else{
            console.log("Could not start "+path+".");
        }
    }
    console.log("Trying using 'java' if set.");
    try {
        java = require('child_process')
            .spawnSync('java', ["-version"]);
    }catch(e){}

    return !!(java && !java.error);
};

function compareVersion(v1, v2) {
    if (typeof v1 !== 'string') return false;
    if (typeof v2 !== 'string') return false;
    v1 = v1.split('.');
    v2 = v2.split('.');
    const k = Math.min(v1.length, v2.length);
    for (let i = 0; i < k; ++ i) {
        v1[i] = parseInt(v1[i], 10);
        v2[i] = parseInt(v2[i], 10);
        if (v1[i] > v2[i]) return 1;
        if (v1[i] < v2[i]) return -1;
    }
    return v1.length === v2.length ? 0: (v1.length < v2.length ? -1 : 1);
}

function checkForUpdates(){
    console.log("Checking for update...");
    const req = {
        headers:{
            'platform':os.platform(),
            'variant':'professional',
            'version':appVersion,
            'ci':uID,
            'license':lic_key,
            'machine':machine
        }
    };
    requestPromise.get(versionUrl,req).then(function (response) {

        let latest_version = JSON.parse(response.body).latest_version;

        if (compareVersion(appVersion,latest_version) < 0 && updateWindow == null){

            updateWindow = new BrowserWindow({
              title: 'Newer Version!',
              width: 400,
              height: 170,
              frame: true,
              resizable: false,
              backgroundColor: "#f3f3f3",
                alwaysOnTop:true,
                icon: path.join(__dirname, 'assets/icons/icon')
          });
          updateWindow.loadFile("version.html");
          updateWindow.webContents.on('new-window', function(event, url){
                event.preventDefault();
                shell.openExternal(url+"?ci="+uID);
            });
          updateWindow.on("closed", () => {
              updateWindow = null;
          });
        }
    }, function (err) {
        return;
    });
}

// Provide API for web application
global.callElectronUiApi = function (args) {
    console.log('Electron called from web app with args "' + args + '"');

    if (args) {
        if (args[0] === 'exit') {
            exit();
        }

        if (args[0] === 'minimize') {
            mainWindow.minimize();
        }

        if (args[0] === 'maximize') {
            if (!mainWindow.isMaximized()) {
                mainWindow.maximize();
            } else {
                mainWindow.unmaximize();
            }
        }
    }
};

function exit() {
    console.log('Kill server process');

    const kill = require('tree-kill');
    kill(serverProcess.pid, 'SIGTERM', function (err) {
        console.log('Server process killed');

        serverProcess = null;
        if (mainWindow != null) {
            mainWindow.close();
        }
        if (licenseWindow != null){
            licenseWindow.close();
        }
        if (loadingWindow!=null) {
            loadingWindow.close();
        }
    });
}

app.on('window-all-closed', function () {
    app.quit();
});

app.on('ready', function () {
    console.log("###### ###### ###### GREETINGS FROM XEOTEK ###### ###### ######");
    console.log("Dear User,");
    console.log("If you are seeing this because you have encountered a problem while using KaDeck, please feel free to contact us: support@kadeck.com.");
    console.log("Greetings from Xeotek Team.");
    console.log("###### ###### ###### X E O T E K ###### ###### ######");

    const storage = require('electron-localstorage');
    storage.setStoragePath(app.getPath('userData')+"/sets.bt");
    if (! storage.getItem("$a")){
        storage.setItem('$a', uuidv4());
    }
    uID = storage.getItem("$a");

    openLoadingWindow();

    if(os.platform() === "darwin"){
        var template = [{
            label: "Application",
            submenu: [
                { label: "KaDeck Desktop "+appVersion },
                { type: "separator" },
                { label: "Quit", accelerator: "Command+Q", click: function() { app.quit(); }}
            ]}, {
            label: "Edit",
            submenu: [
                { label: "Undo", accelerator: "CmdOrCtrl+Z", selector: "undo:" },
                { label: "Redo", accelerator: "Shift+CmdOrCtrl+Z", selector: "redo:" },
                { type: "separator" },
                { label: "Cut", accelerator: "CmdOrCtrl+X", selector: "cut:" },
                { label: "Copy", accelerator: "CmdOrCtrl+C", selector: "copy:" },
                { label: "Paste", accelerator: "CmdOrCtrl+V", selector: "paste:" },
                { label: "Select All", accelerator: "CmdOrCtrl+A", selector: "selectAll:" }
            ]}
        ];

        Menu.setApplicationMenu(Menu.buildFromTemplate(template));
    }
    platform = process.platform;

    try {
        if (platform === 'win32') {
            serverProcess = require('child_process')
                .spawn(app.getAppPath() + '/electron-kadeck/bin/KaDeck.bat');
        } else {
            serverProcess = require('child_process')
                .spawn(app.getAppPath() + '/electron-kadeck/bin/KaDeck');
        }
    }catch(e){
        console.log("Critical error", e);
    }
    if (!serverProcess) {
        console.error('Unable to start server from ' + app.getAppPath());
        app.quit();
        return;
    }
    serverProcess.on('exit', function (code, signal) {
        console.log('KaDeck Backend process exited with ' +
            `code ${code} and signal ${signal}`);
        backendCrashed = true;
    });

    serverProcess.on('error', function (error) {
        console.log('KaDeck Backend process exited with ' +
            `error: ${error}`);
    });

    serverProcess.stderr.on('data', (chunk) => {
        console.log(`KaDeck Backend `+ chunk);
    });
    serverProcess.stdout.on('data', function (data) {
        console.log('KaDeck Backend ' + data);
    });

    console.log("Server PID: " + serverProcess.pid);

    startUp();

    // Register a shortcut listener.
    const ret = globalShortcut.register('CommandOrControl+Shift+`', () => {
        console.log('Bring to front shortcut triggered');
        if (mainWindow) {
            mainWindow.focus();
        }
    })
});
const openWindow = function () {

    const selectionMenu = Menu.buildFromTemplate([
        {role: 'copy'},
        {type: 'separator'},
        {role: 'selectall'},
    ]);

    const inputMenu = Menu.buildFromTemplate([
        {role: 'cut', accelerator: "CmdOrCtrl+X"},
        {role: 'copy',  accelerator: "CmdOrCtrl+C"},
        {role: 'paste', accelerator: "CmdOrCtrl+V"},
        {type: 'separator'},
        {role: 'selectall', accelerator: "CmdOrCtrl+A"},
    ]);

    mainWindow = new BrowserWindow({
        title: 'KaDeck Desktop',
        width: 1280,
        height: 768,
        frame: true,
        backgroundColor: "#fbfbfb",
        icon: path.join(__dirname, 'assets/icons/icon'),
        show:false
    });



    mainWindow.loadURL(appUrl,options);
    mainWindow.webContents.on('context-menu', (e, props) => {
        const { selectionText, isEditable } = props;
        if (isEditable) {
            inputMenu.popup(mainWindow);
        } else if (selectionText && selectionText.trim() !== '') {
            selectionMenu.popup(mainWindow);
        }
    });

    mainWindow.webContents.session.clearCache(()=>{});
    // mainWindow.loadFile('index.html');
    // uncomment to show debug tools
    //  mainWindow.webContents.openDevTools();

    mainWindow.on('closed', function () {
        mainWindow = null;
    });

    mainWindow.on('show', ()=>{
    });


    mainWindow.webContents.on('new-window', function(event, url){
        event.preventDefault();
        shell.openExternal(url+"?ci="+uID);
    });

    mainWindow.on('close', function (e) {
        if (serverProcess) {
            e.preventDefault();
            exit();
        }
    });

    mainWindow.on("ready-to-show", ()=>{
        mainWindow.loadURL(appUrl,options);
        mainWindow.show();
        if (loadingWindow!=null) {
            loadingWindow.close();
        }
        if (licenseWindow!=null) {
            licenseWindow.close();
        }
    });
};

let count = 0;
const maxCount = 30;
const startUp = function () {
    const req = {
        headers:headers
    };
    requestPromise.get(appUrl,req).then(function (response) {
        console.log('KaDeck started!');
        console.log(response);

            checkForUpdates();
            setTimeout(function(){
                openWindow();
            }, 300);

    }, function (response) {
        console.log('Starting up..');
        if (response && response.headers&&response.headers.lic_status){
            console.log("License not valid.");
            licenseScreen();
            return;
        }else {
            if (count===maxCount){
                checkForUpdates();
            }
        }
        if (backendCrashed){
           openErrorDialog("Critical failure - KaDeck Backend process could not be started. See logs for more information or contact support.")
            if (loadingWindow != null)
                loadingWindow.close();
            checkForUpdates();
        }else{
            setTimeout(function () {
                count++;
                startUp();
            }, 400);
        }
    });
};

app.on('will-quit', () => {
    // Unregister all shortcuts.
    globalShortcut.unregisterAll();
});

function licenseScreen() {
    if (licenseActivationPrompted===true){
        exit();
        return;
    }
    licenseWindow = new BrowserWindow({
        title: 'License Activation Center',
        width: 850,
        height: 500,
        frame: true,
        resizable: false,
        backgroundColor: "#fff",
        show:false,
        icon: path.join(__dirname, 'assets/icons/icon')
    });
    licenseWindow.loadFile("nolicense.html");

    licenseWindow.webContents.on('new-window', function(event, url){
        event.preventDefault();
        shell.openExternal(url+"?ci="+uID);
    });
    licenseWindow.on("close", (e) => {
        e.preventDefault;
        openLoadingWindow();
        startUp();
    });
    licenseWindow.on("closed", () => {
        licenseWindow = null;
    });
    licenseWindow.on("ready-to-show", ()=>{
        licenseWindow.show();
    });
    licenseWindow.on("show", () =>{
        licenseActivationPrompted = true;
        if (loadingWindow!=null)
            loadingWindow.close();
    });

}

function uuidv4() {
    return 'xxxxxyyyxxxyy'.replace(/[xy]/g, function(c) {
        var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
        return v.toString(20)+v.toString(10);
    });
}
