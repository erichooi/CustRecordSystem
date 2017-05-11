PRAGMA FOREIGN_KEYS = 1;

create table CUSTOMER(
    customerID INTEGER PRIMARY KEY AUTOINCREMENT,
    customerName TEXT,
    address1 TEXT,
    address2 TEXT,
    city TEXT,
    state TEXT,
    postalCode INTEGER,
    country TEXT
);

create table PHONE(
    phoneID INTEGER PRIMARY KEY AUTOINCREMENT,
    customerID INTEGER,
    phoneNum INTEGER,
    FOREIGN KEY(customerID) REFERENCES CUSTOMER(customerID)
);

create table ORDERS(
    orderID INTEGER PRIMARY KEY AUTOINCREMENT,
    customerID INTEGER,
    orderDate TEXT default current_date,
    requireDate TEXT,
    status NUMERIC default 0, -- 0 = incomplete, 1 = complete, 2 = cancel
    FOREIGN KEY(customerID) REFERENCES CUSTOMER(customerID)
);

create table PRODUCT(
    productID INTEGER PRIMARY KEY AUTOINCREMENT,
    productName TEXT,
    productCode TEXT,
    price REAL
);

create table ORDERDETAIL(
    orderDetailID INTEGER PRIMARY KEY AUTOINCREMENT,
    orderID INTEGER,
    productID INTEGER,
    quantity INTEGER,
    FOREIGN KEY(orderID) REFERENCES ORDERS(orderID),
    FOREIGN KEY(productID) REFERENCES PRODUCT(productID)
);
