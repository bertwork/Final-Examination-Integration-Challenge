#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// ========================================================= UI CLASS =========================================================
/**
 * @class UI
 * @brief Provides static utility methods for user interface components
 * 
 * This class handles common UI elements like headers and separators
 * to maintain consistent formatting throughout the application.
 */
class UI {
  public:
    /**
     * @brief Displays a formatted header with the given title
     * @param title The title to display in the header
     * 
     */
    static void header(const string &title) {
      cout << "\n>>> ===== " << title << " ===== <<<\n";
    }

    /**
     * @brief Prints a horizontal line separator
     * 
     * Creates a 45-character line using '-' characters
     * to visually separate sections of the interface.
     */
    static void line() {
      cout << string(45, '-') << "\n";
    }

    static void goodbyeMessage(const string &message) {
      cout << message;
    }

    // @brief Pauses execution until the user presses Enter once.
    static void pauseBuffer() {
      cout << "\n>>> Press Enter to continue...";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin.get();
    }
};

// ================================================== INPUT VALIDATOR CLASS ======================================================
/**
 * @class InputValidator
 * @brief Handles all user input validation with type and range checking
 * 
 * This class provides static methods to safely read and validate
 * different types of user input, preventing crashes from invalid data.
 */
class InputValidator {
  public:
    /**
     * @brief Template method to get validated input of any type
     * @tparam T The data type to read (int, double, etc.)
     * @param prompt The message to display to the user
     * @param var Reference to store the validated input
     * 
     * Continuously prompts until valid input is received.
     * Clears error flags and invalid input from the stream.
     */
    template < typename T >
    static void getValidated(const string& prompt, T& var) {
      while (true) {
        cout << prompt;
        cin >> var;

        if (!cin.fail()) break;

        cout << "\n[ERROR] Invalid input! Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      }
    }

    /**
     * @brief Gets a validated integer choice within a specified range
     * @param prompt The prompt message to display
     * @param min Minimum acceptable value (inclusive)
     * @param max Maximum acceptable value (inclusive)
     * @return The validated integer choice
     * 
     * Used for menu selections where input must be within a specific range.
     */
    static int getValidatedChoice(const string& prompt, int min, int max) {
      int choice;

      do {
        getValidated(prompt, choice);
        if (choice < min || choice > max)
          cout << "[ERROR] Choice must be " << min << "-" << max << ". Try again.\n";
      } while (choice < min || choice > max);

      return choice;
    }

    /**
     * @brief Gets a validated double value within a specified range
     * @param prompt The prompt message to display
     * @param min Minimum acceptable value (inclusive)
     * @param max Maximum acceptable value (inclusive)
     * @return The validated double value
     * 
     * Used for numeric inputs like grades or monetary amounts.
     */
    static double getValidatedDouble(const string & prompt, double min, double max) {
      double value;

      do {
        getValidated(prompt, value);
        if (value < min || value > max)
          cout << "[ERROR] Value must be between " << min << " and " << max << ". Try again.\n";
      } while (value < min || value > max);

      return value;
    }

    /**
     * @brief Gets a validated yes/no response from the user.
     * 
     * Uses the generic getValidated() template to safely read a string input,
     * then normalizes it to lowercase for case-insensitive comparison.
     * Accepts both short and long forms ("y" / "yes", "n" / "no").
     * 
     * The function loops until a valid yes/no response is entered.
     * 
     * @param prompt The message to display to the user.
     * @return true  If the user enters "y" or "yes".
     * @return false If the user enters "n" or "no".
     */
    static bool getValidatedYesNo(const string& prompt) {
      string input;

      do {
        getValidated(prompt + " (y/n): ", input);

        // convert to lowercase
        for (char& c : input) c = tolower(c);

        if (input == "y" || input == "yes") return true;
        if (input == "n" || input == "no") return false;

        cout << "[ERROR] Please type 'y' or 'n'.\n";

        } while (true);
    }
};

// ================================================== VIRTUAL STUDENT INFO CLASS =================================================
/**
 * @class VirtualStudentInfo
 * @brief Displays static student information
 * 
 * This class provides a simple interface to show predefined
 * student details when selected from the main menu.
 */
class VirtualStudentInfo {
  public:
    /**
     * @brief Runs the Virtual Student Info activity
     * 
     * Displays a formatted header followed by the student's
     * personal and academic information.
     */
    void run() {
      UI::header("Virtual Student Info");

      // Display static student information
      cout << "Name: Alberto Jr Deniros\n"
           << "Section and Course: BSCS 1-A\n"
           << "AGE: 23\n"
           << "GENDER: MALE\n"
           << "CODING DEVICES: Desktop Computer\n"
      ;
      
      UI::pauseBuffer();
    }
};

// ================================================== STUDENT GRADE EVALUATOR CLASS =================================================
/**
 * @class StudentGradeEvaluator
 * @brief Evaluates student grades and determines pass/fail status
 * 
 * This class collects four grades from the user, calculates the average,
 * and compares it against a passing threshold to determine the result.
 */
class StudentGradeEvaluator {
  private:
    /**
     * @struct Grade
     * @brief Represents a single grade with name and value
     */
    struct Grade {
      string name;    // Name of the grading period (e.g., "Prelim")
      double value;   // Numerical grade value (0-100)
    };

  public:
    /**
     * @brief Runs the Student Grade Evaluator activity
     * 
     * Prompts for four grades (Prelim, Midterm, PreFinal, Final),
     * calculates the average, and displays pass/fail status.
     */
    void run() {
      UI::header("Student Grade Evaluator");

      const int NUMBER_OF_GRADES = 4;      // Total number of grades to collect
      const int PASSING_GRADE = 80;        // Minimum average required to pass
      const int MIN_GRADE = 0;             // Min Grade required
      const int MAX_GRADE = 100;           // Max Grade required

      // Initialize grade entries with names and default values
      Grade grades[NUMBER_OF_GRADES] = {
        {"Prelim", 0},
        {"Midterm", 0},
        {"PreFinal", 0},
        {"Final", 0}
      };

      double sum = 0; // Accumulator for grade total

      // Collect and validate each grade
      for (int i = 0; i < NUMBER_OF_GRADES; i++) {
        grades[i].value = InputValidator::getValidatedDouble(
          "Enter " + grades[i].name + " Grade: ", MIN_GRADE, MAX_GRADE
        );
        sum += grades[i].value;
      }

      // Calculate average grade
      double average = sum / NUMBER_OF_GRADES;

      // Display results with formatting
      UI::line();
      cout << "Passing grade: " << PASSING_GRADE << "\n";
      cout << "Your average: " << average << "\n";
      cout << "REMARKS: ";

      // Determine and display pass/fail status
      if (average >= PASSING_GRADE) {
        UI::header("PASADO KA BOI!!");
      } else {
        UI::header("BAGSAK KA BOI!!");
      }
      UI::line();

      UI::pauseBuffer();
    };
};

// ================================================== TRIANGLE LOOP ACTIVITY CLASS =================================================
/**
 * @class TriangleLoopActivity
 * @brief Generates and displays triangle patterns using asterisks
 * 
 * This class provides an interactive interface for creating
 * right-aligned and inverted triangle patterns of specified heights.
 */
class TriangleLoopActivity {
  private:
    /**
     * @brief Displays a right-aligned triangle pattern
     * @param height The number of rows in the triangle
     * 
     * Example (height = 3):
     * *
     * **
     * ***
     */
    void displayRightTriangle(int height) {
      for (int i = 0; i < height; i++) {
        for(int j = 0; j <= i; j++) {
          cout << "*";
        }
        cout << "\n";
      }
    }
    
    /**
     * @brief Displays an inverted triangle pattern
     * @param height The number of rows in the triangle
     * 
     * Example (height = 3):
     * ***
     * **
     * *
     */
    void displayInvertedTriangle(int height) {
      for (int i = 0; i < height; i++) {
        for(int j = height; j > i; j--) {
          cout << "*";
        }
        cout << "\n";
      }
    }

  public:
    /**
     * @brief Runs the Triangle Loop Activity
     * 
     * Provides a menu for users to choose triangle type,
     * specify height, and view the generated patterns.
     */
    void run() {
      // constant value of min and max value to required to pass
      const int MIN_MENU_OPTION = 1;
      const int MAX_MENU_OPTION = 4;
      const int MIN_HEIGHT = 1;
      const int MAX_HEIGHT = 20;

      UI::header("Triangle Loop Activity");
      int menuChoice, height;

      // Main activity loop
      while (true) {
        cout << "Triangle Options:\n"
             << "1. Right Triangle\n"
             << "2. Inverted Triangle\n"
             << "3. Both\n"
             << "4. Exit\n";
        UI::line();

        // Get user's triangle choice
        menuChoice = InputValidator::getValidatedChoice("Enter choice (1-4): ", MIN_MENU_OPTION, MAX_MENU_OPTION);

        // Exit Triangle Activity
        if (menuChoice == 4) {
          UI::goodbyeMessage("Exiting Triangle Activity...\n");
          UI::goodbyeMessage("Successfully Navigated to Main Menu\n\n");
          break;
        }

        // Get triangle height (limited to 1-20 for display purposes)
        height = InputValidator::getValidatedChoice("Enter height (1-20): ", MIN_HEIGHT, MAX_HEIGHT);

        cout << "\n";
        switch (menuChoice) {
          case 1:
            cout << "Right Triangle:\n";
            displayRightTriangle(height);
            UI::pauseBuffer();
            break;
          case 2:
            cout << "Inverted Triangle:\n";
            displayInvertedTriangle(height);
            UI::pauseBuffer();
            break;
          case 3:
            cout << "Right Triangle:\n";
            displayRightTriangle(height);
            cout << "\nInverted Triangle:\n";
            displayInvertedTriangle(height);
            UI::pauseBuffer();
            break;
          default:
            cout << "[ERROR] Choice must be 1-4. Try again.";
        }
        cout << "\n";
      }
    }
};

// ================================================== CURRENCY EXCHANGE CALCULATOR ================================================
/**
 * @class CurrencyExchangeCalculator
 * @brief Converts Philippine Pesos to multiple foreign currencies
 * 
 * This class handles currency conversion with real-time rates,
 * applies transaction fees, and displays comprehensive results.
 */
class CurrencyExchangeCalculator {
  private:
    // Current exchange rates (PHP to foreign currency)
    const double USD_RATE = 58.2554;  // 1 USD = ₱58.2554
    const double EUR_RATE = 67.6375;  // 1 EUR = ₱67.6375
    const double JPY_RATE = 0.3818;   // 1 JPY = ₱0.3818
    const double AUD_RATE = 38.3071;  // 1 AUD = ₱38.3071
    const double TRANSACTION_FEE_RATE = 0.05; // 5% transaction fee

    /**
     * @brief Displays current exchange rates and transaction policies
     */
    void displayRates() {
      UI::header("Today's Exchange Rates");
      UI::line();

      cout << fixed << setprecision(4);
      // Display conversion rates from PHP to foreign currencies
      cout << "USD ($)   : 1 PHP = " << (1.0 / USD_RATE) << " USD\n";
      cout << "EUR (€)   : 1 PHP = " << (1.0 / EUR_RATE) << " EUR\n";
      cout << "JPY (¥)   : 1 PHP = " << (1.0 / JPY_RATE) << " JPY\n";
      cout << "AUD (A$)  : 1 PHP = " << (1.0 / AUD_RATE) << " AUD\n";

      UI::line();
      cout << setprecision(0) << "Transaction Fee" << ": " << (TRANSACTION_FEE_RATE * 100) << "%\n";
      cout << "Minimum Transaction" << ": ₱100\n";
      cout << "Maximum Transaction" << ": ₱100,000\n";
      UI::line();
    }

    /**
     * @brief Displays formatted conversion results
     * @param amountInPHP Original PHP amount before fees
     * @param fee Transaction fee deducted
     * @param netPHP Net PHP amount after fee deduction
     * @param usd Converted amount in US Dollars
     * @param eur Converted amount in Euros
     * @param jpy Converted amount in Japanese Yen
     * @param aud Converted amount in Australian Dollars
     */
    void displayConversion(double amountInPHP, double fee, double netPHP, double usd, double eur, double jpy, double aud) {
      UI::header("Conversion Result");
      UI::line();
      cout << fixed << setprecision(2);

      // Display transaction summary
      cout << setw(18) << left << "Original Amount" << ": ₱" << amountInPHP << "\n";
      cout << setw(18) << left << "Transaction Fee" << ": ₱" << fee << "\n";
      cout << setw(18) << left << "Net Amount" << ": ₱" << netPHP << "\n";

      // Table column widths for aligned output
      const int label_w = 14;  // Currency label width
      const int rate_w  = 14;  // Exchange rate width
      const int val_w   = 12;  // Converted value width

      UI::line();
      // Table header
      cout << left << setw(label_w) << "Currency" 
           << left << setw(rate_w) << "Rate (PHP per ₱1)" 
           << right << setw(val_w) << "Converted" << "\n";

      // Display each currency conversion
      cout << left << setw(label_w) << "USD ($)       " 
           << left << setw(rate_w) << USD_RATE << "     " 
           << usd << " USD\n";

      cout << left << setw(label_w) << "EUR (€)       " 
           << left << setw(rate_w) << EUR_RATE << "     " 
           << eur << " EUR\n";

      cout << left << setw(label_w) << "JPY (¥)       " 
           << left << setw(rate_w) << JPY_RATE << "     " 
           << jpy << " JPY\n";

      cout << left << setw(label_w) << "AUD (A$)      " 
           << left << setw(rate_w) << AUD_RATE << "     " 
           << aud << " AUD\n";
    }

    /**
     * @brief Handles the currency conversion process
     * 
     * Guides user through amount input, fee confirmation,
     * calculation, and result display.
     */
    void convertCurrency() {
      double amountInPHP;

      // Get PHP amount with validation
      amountInPHP = InputValidator::getValidatedDouble(
        "Enter amount in PHP (₱): ", 100, 100000
      );

      // Confirm transaction with user
      cout << "A 5% transaction fee will be charged for the exchange.\n";
      if (!InputValidator::getValidatedYesNo("Would you like to proceed?")) {
        UI::goodbyeMessage("Transaction cancelled.\n");
        return;
      }

      // Calculate fee and net amount
      double fee = amountInPHP * TRANSACTION_FEE_RATE;
      double netPHP = amountInPHP - fee;

      // Convert to all supported currencies
      double usd = netPHP / USD_RATE;
      double eur = netPHP / EUR_RATE;
      double jpy = netPHP / JPY_RATE;
      double aud = netPHP / AUD_RATE;

      // Display results
      displayConversion(amountInPHP, fee, netPHP, usd, eur, jpy, aud);
    }

  public:
    /**
     * @brief Runs the Currency Exchange Calculator activity
     * 
     * Provides a menu for currency exchange operations
     * including conversion and rate viewing.
     */
    void run() {
      const int MIN_MENU_OPTION = 1;
      const int MAN_MENU_OPTION = 3;
      int menuChoice;

      // Main calculator loop
      while (true) {
        UI::header("Currency Exchange Calculator");

        cout << "Currency Exchange Options:\n"
             << "1. Exchange Currency\n"
             << "2. View Rates\n"
             << "3. Exit\n"
        ;

        UI::line();
        menuChoice = InputValidator::getValidatedChoice("Enter choice (1-3): ", MIN_MENU_OPTION, MAN_MENU_OPTION);

        // Exit Currency Exchange Calculator Activity
        if (menuChoice == 3) {
          UI::goodbyeMessage("Exiting Currency Exchange Calculator...\n");
          UI::goodbyeMessage("Successfully Navigated to Main Menu\n\n");
          break;
        }

        switch (menuChoice) {
          case 1:
            convertCurrency();
            UI::pauseBuffer();
            break;
          case 2:
            displayRates();
            UI::pauseBuffer();
            break;
          default:
            cout << "[ERROR] Choice must be 1-3. Try again.\n";
        }
      }
    }
};

// ======================================================= PROGRAM CLASS ==========================================================
/**
 * @class Program
 * @brief Main controller class for the Programming Activity System
 * 
 * This class manages the application lifecycle, displays the main menu,
 * and coordinates between different activity modules.
 */
class Program {
  private:
    // Available menu options
    vector <string> menuItems = {
      "Virtual Student Info",
      "Student Grade Evaluator",
      "Triangle Loop Activity",
      "Currency Exchange Calculator",
      "Exit Program"
    };

    // Activity module instances
    VirtualStudentInfo studentInfo;
    StudentGradeEvaluator gradeEvaluator;
    TriangleLoopActivity triangleActivity;
    CurrencyExchangeCalculator currencyCalculator;

  public:
    /**
     * @brief Main application entry point
     * 
     * Displays welcome message and main menu in a loop,
     * routing user choices to appropriate activity modules.
     */
    void run() {
      int menuChoice;

      // Display welcome banner
      cout << "\n" << string(45, '*') << "\n";
      cout << "   WELCOME TO PROGRAMMING ACTIVITY SYSTEM\n";
      cout << string(45, '*') << "\n";

      // Main application loop
      while (true) {
        UI::line();
        cout << ">>> ===== PROGRAMMING ACTIVITY MENU ===== <<<\n";
        UI::line();

        // Display dynamic menu from menuItems vector
        for (size_t i = 0; i < menuItems.size(); ++i) {
          cout << "[" << i + 1 << "] " << menuItems[i] << "\n";
        }
        UI::line();

        // Get user's menu selection
        menuChoice = InputValidator::getValidatedChoice(
          "Enter choice (1-" + to_string(menuItems.size()) + "): ",
          1,
          static_cast <int> (menuItems.size())
        );

        // Route to selected activity
        switch (menuChoice) {
        case 1:
          studentInfo.run();
          break;
        case 2:
          gradeEvaluator.run();
          break;
        case 3:
          triangleActivity.run();
          break;
        case 4:
          currencyCalculator.run();
          break;
        case 5:
          UI::goodbyeMessage("Exiting program... Goodbye!\n");
          return; // Exit application
        default:
          cout << "[ERROR] Choice must be 1-5. Try again.\n";
        }
      }
    }
};

// ================================================== MAIN FUNCTION =================================================
/**
 * @brief Application entry point
 * 
 * Creates the main Program instance and starts the application.
 * 
 * @return int Exit status (0 for successful execution)
 */
int main() {
  Program program;          // Create main program instance
  program.run();            // Start the application
  
  return 0;                 // Return success status
}