﻿#include "interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRadioButton>
#include <QApplication>
#include <QtDebug>
#include "function.h"
#include "realnumber.h"
#include "sin.h"
#include "si.h"


TInterface::TInterface(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void TInterface::setupUI()
{
    setWindowTitle("Вычисление функций");
    setMaximumSize(400, 200);

    mainLayout = new QVBoxLayout(this);

    // Поле ввода x
    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Введите x");
    mainLayout->addWidget(inputField);

    // Поле ввода точности
    precisionField = new QLineEdit(this);
    precisionField->setPlaceholderText("Введите точность");
    mainLayout->addWidget(precisionField);

    // Кнопка "Вычислить sin(x)"
    calculateSinButton = new QPushButton("Вычислить sin(x)", this);
    connect(calculateSinButton, &QPushButton::clicked, this, &TInterface::calculateSin);
    mainLayout->addWidget(calculateSinButton);

    // Кнопка "Вычислить Si(x)"
    calculateSiButton = new QPushButton("Вычислить Si(x)", this);
    connect(calculateSiButton, &QPushButton::clicked, this, &TInterface::calculateSi);
    mainLayout->addWidget(calculateSiButton);

    // Поле вывода результата
    outputField = new QLineEdit(this);
    outputField->setReadOnly(true);
    outputField->setPlaceholderText("Результат будет здесь...");
    mainLayout->addWidget(outputField);

    // Кнопка "Очистить"
    clearButton = new QPushButton("Очистить", this);
    connect(clearButton, &QPushButton::clicked, this, &TInterface::clearOutput);
    mainLayout->addWidget(clearButton);

    // Кнопка "Выход"
    exitButton = new QPushButton("Выход", this);
    connect(exitButton, &QPushButton::clicked, this, &TInterface::exitApplication);
    mainLayout->addWidget(exitButton);

    setLayout(mainLayout);
}

TInterface::~TInterface()
{
    delete outputField; // Поле вывода результата
    delete inputField; // Поле ввода x
    delete precisionField; // Поле ввода точности
    delete clearButton; // Кнопка очистки
    delete calculateSinButton; // Кнопка вычисления sin(x)
    delete calculateSiButton; // Кнопка вычисления Si(x)
    delete exitButton; // Кнопка выхода
    delete mainLayout; // Основной макет
}

void TInterface::calculateSin()
{
    bool okX, okPrecision;
    const TRealNumber x = inputField->text().toDouble(&okX);
    const int precision = precisionField->text().toInt(&okPrecision);

    if (okX && okPrecision && precision >= 1)
    {
        TFsin<TRealNumber> func(precision); // теперь вычисление производных идет в классе
        TRealNumber result = func.getValue(x);

        QString resStr;
        resStr << result;

        func.setPrintMode(EPrintModeCanonical);
        QString loggingMessage = "";
        loggingMessage << func;
        qDebug() << loggingMessage;


        QString strX;
        strX << x;
        outputField->setText("sin(" + strX + ") = "+ resStr);
        return;
    }

    outputField->setText("Ошибка ввода!");
}

void TInterface::calculateSi()
{
    bool okX, okPrecision;
    const TRealNumber x = inputField->text().toDouble(&okX);
    const int precision = precisionField->text().toInt(&okPrecision);

    if (okX && okPrecision && precision >= 1)
    {
        TFsi<TRealNumber> func(precision); // теперь вычисление производных идет в классе
        TRealNumber result = func.getValue(x);

        QString resStr;
        resStr << result;

        func.setPrintMode(EPrintModeCanonical);
        QString loggingMessage = "";
        loggingMessage << func;
        qDebug() << loggingMessage;

        QString strX;
        strX << x;
        outputField->setText("Si(" + strX + ") = "+ resStr);
        return;
    }

    outputField->setText("Ошибка ввода!");
}

void TInterface::clearOutput()
{
    outputField->clear(); // Очистка поля вывода
}

void TInterface::exitApplication()
{
    QApplication::quit(); // Завершение приложения
}

