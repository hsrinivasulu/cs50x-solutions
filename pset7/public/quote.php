<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $quote = lookup(filter($_POST["symbol"]));
        
        if ($quote == FALSE)
            apologize("Ticker does not exist");
        
        // display the data
        render("quote_display.php", ["name" => $quote["name"], "symbol" => $quote["symbol"], "price" => $quote["price"]]);
    }

?>
