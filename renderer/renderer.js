/**
 * This file is loaded via the <script> tag in the index.html file and will
 * be executed in the renderer process for that window. No Node.js APIs are
 * available in this process because `nodeIntegration` is turned off and
 * `contextIsolation` is turned on. Use the contextBridge API in `preload.js`
 * to expose Node.js functionality from the main process.
 */

const { ipcRenderer } = require('electron');

document.getElementById('addProductButton').addEventListener('click', async () => {
    const product = {
        productID: document.getElementById('productID').value,
        name: document.getElementById('name').value,
        category: document.getElementById('category').value,
        price: parseFloat(document.getElementById('price').value),
        stockQuantity: parseInt(document.getElementById('stockQuantity').value),
        description: document.getElementById('description').value
    };

    try {
        await ipcRenderer.invoke('create-product', product);
        alert(`Product with ID ${product.productID} created successfully.`);
    } catch (error) {
        alert(error.message); // Show error message if the product already exists
        console.error('Error creating product:', error);
    }
});

document.getElementById('fetchProductsButton').addEventListener('click', async () => {
    // Log when the button is clicked to confirm the event listener is working
    console.log('Fetch Products Button Clicked'); 

    // Fetch the products from the backend using IPC
    const products = await ipcRenderer.invoke('get-all-products');
    console.log(products); // Check what is returned

    // Clear the previous product list in the UI
    const productList = document.getElementById('productList');
    productList.innerHTML = '';

    // Update the UI with the fetched products
    products.forEach(product => {
        const listItem = document.createElement('li');
        listItem.textContent = `${product.name} - ${product.category} - $${product.price}`;
        productList.appendChild(listItem);
    });
});


// Function to remove a product
async function removeProduct(productID) {
    const success = await ipcRenderer.invoke('remove-product', productID);
    if (success) {
        console.log(`Product with ID ${productID} removed successfully.`);
    } else {
        console.log(`Failed to remove product with ID ${productID}.`);
    }
}

// Function to update a product
async function updateProduct(productID, updatedProduct) {
    const success = await ipcRenderer.invoke('update-product', productID, updatedProduct);
    if (success) {
        console.log(`Product with ID ${productID} updated successfully.`);
    } else {
        console.log(`Failed to update product with ID ${productID}.`);
    }
}

// Remove Product
document.getElementById('removeProductBtn').addEventListener('click', async () => {
    const productID = document.getElementById('removeProductID').value;
    
    try {
        const success = await ipcRenderer.invoke('remove-product', productID);
        if (success) {
            alert(`Product with ID ${productID} removed successfully.`);
        } else {
            alert(`Failed to remove product with ID ${productID}.`);
        }
    } catch (error) {
        console.error('Error removing product:', error);
    }
});

document.getElementById('updateProductBtn').addEventListener('click', async () => {
    const productID = document.getElementById('updateProductID').value;
    const updatedProduct = {
        name: document.getElementById('updatedName').value,
        category: document.getElementById('updatedCategory').value,
        price: parseFloat(document.getElementById('updatedPrice').value),
        stockQuantity: parseInt(document.getElementById('updatedStockQuantity').value),
        description: document.getElementById('updatedDescription').value
    };

    try {
        const success = await ipcRenderer.invoke('update-product', productID, updatedProduct);
        if (success) {
            alert(`Product with ID ${productID} updated successfully.`);
        } else {
            alert(`Failed to update product with ID ${productID}. It may not exist.`);
        }
    } catch (error) {
        console.error('Error updating product:', error);
    }
});
