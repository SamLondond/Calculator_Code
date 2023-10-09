#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <cmath>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0) : QWidget(parent) {
        setWindowTitle("Simple Calculator");
        
        layout = new QGridLayout(this);

        display = new QLineEdit(this);
        display->setAlignment(Qt::AlignRight);
        display->setReadOnly(true);
        layout->addWidget(display, 0, 0, 1, 4);

        const char *buttonText[16] = {
            "7", "8", "9", "/",
            "4", "5", "6", "*",
            "1", "2", "3", "-",
            "0", ".", "=", "+"
        };
        
        buttons[16];
        for (int i = 0; i < 16; ++i) {
            buttons[i] = createButton(buttonText[i]);
        }

        layout->addWidget(buttons[0], 1, 0);
        layout->addWidget(buttons[1], 1, 1);
        layout->addWidget(buttons[2], 1, 2);
        layout->addWidget(buttons[3], 1, 3);
        layout->addWidget(buttons[4], 2, 0);
        layout->addWidget(buttons[5], 2, 1);
        layout->addWidget(buttons[6], 2, 2);
        layout->addWidget(buttons[7], 2, 3);
        layout->addWidget(buttons[8], 3, 0);
        layout->addWidget(buttons[9], 3, 1);
        layout->addWidget(buttons[10], 3, 2);
        layout->addWidget(buttons[11], 3, 3);
        layout->addWidget(buttons[12], 4, 0);
        layout->addWidget(buttons[13], 4, 1);
        layout->addWidget(buttons[14], 4, 2);
        layout->addWidget(buttons[15], 4, 3);

        connectButtons();
    }

private slots:
    void buttonClicked() {
        QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
        if (!clickedButton)
            return;

        QString clickedText = clickedButton->text();

        if (clickedText == "=") {
            // Calculate the result
            QString expression = display->text();
            double result = calculate(expression);
            display->setText(QString::number(result));
        } else if (clickedText == "C") {
            // Clear input
            display->clear();
        } else {
            // Add to the input
            display->setText(display->text() + clickedText);
        }
    }

private:
    QGridLayout *layout;
    QLineEdit *display;
    QPushButton *buttons[16];

    QPushButton* createButton(const QString& text) {
        QPushButton *button = new QPushButton(text, this);
        if (text == "=" || text == "C") {
            connect(button, &QPushButton::clicked, this, &Calculator::buttonClicked);
        } else {
            connect(button, &QPushButton::clicked, this, &Calculator::buttonClicked);
        }
        return button;
    }

    void connectButtons() {
        for (int i = 0; i < 16; ++i) {
            if (buttons[i]) {
                connect(buttons[i], &QPushButton::clicked, this, &Calculator::buttonClicked);
            }
        }
    }

    double calculate(const QString& expression) {
        // This function can perform the calculation of the expression
        // and needs to parse and calculate based on the format of the expression.
        // In this simplified example, we support basic addition, subtraction,
        // multiplication, and division only.
        // A real calculator application would require more complex logic
        // to handle various operators and functions.
        // This is just a simplified example.
        return evalExpression(expression);
    }

    double evalExpression(const QString& expression) {
        // Simplified expression evaluation function, supporting only
        // addition, subtraction, multiplication, and division.
        // Note that this is not a complete expression evaluation implementation,
        // just a demonstration.
        return evalSimpleExpression(expression);
    }

    double evalSimpleExpression(const QString& expression) {
        QStringList tokens = expression.split(' ');
        double result = tokens[0].toDouble();
        for (int i = 1; i < tokens.size(); i += 2) {
            QString op = tokens[i];
            double operand = tokens[i + 1].toDouble();
            if (op == "+") {
                result += operand;
            } else if (op == "-") {
                result -= operand;
            } else if (op == "*") {
                result *= operand;
            } else if (op == "/") {
                if (operand != 0.0) {
                    result /= operand;
                } else {
                    display->setText("Error: Division by zero");
                    return NAN;
                }
            }
        }
        return result;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Calculator calculator;
    calculator.show();

    return app.exec();
}

