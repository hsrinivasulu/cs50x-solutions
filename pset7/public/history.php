<?php

    // configuration
    require("../includes/config.php"); 
    
    $id = $_SESSION["id"];
    
    // obtain transaction data
    $records = array_filter(query("SELECT * FROM `transactions` WHERE id = ?", $id));
    
    // render portfolio
    if (!empty($records))
        render("transactions.php", ["title" => "History", "records" => $records]);
    else
        apologize("You haven't made any transactions yet.");
?>
