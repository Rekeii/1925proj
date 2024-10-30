const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');

// Load the compiled C++ addon
const cpp_inventory = require('./build/Release/cpp_inventory');

function createWindow() {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, 'renderer.js'),
            nodeIntegration: true,
            contextIsolation: false
        }
    });

    win.loadFile('renderer/index.html');
}

app.whenReady().then(() => {
    createWindow();

    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) {
            createWindow();
        }
    });
});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

// IPC handlers to communicate with frontend
ipcMain.handle('create-product', (event, product) => {
    return cpp_inventory.createProduct(
        product.productID,
        product.name,
        product.category,
        product.price,
        product.stockQuantity,
        product.description
    );
});

ipcMain.handle('remove-product', (event, productID) => {
    return cpp_inventory.removeProduct(productID);
});

ipcMain.handle('update-product', (event, productID, updatedProduct) => {
    console.log('Updating Product:', productID, updatedProduct);
    return cpp_inventory.updateProduct(productID, updatedProduct);
});


ipcMain.handle('get-all-products', () => {
    console.log('Fetching all products'); // Log the fetch request
    return cpp_inventory.getAllProducts();
});

