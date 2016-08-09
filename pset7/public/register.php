<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]) || empty($_POST["password"]) || empty($_POST["email"]))
            apologize("One or more fields were left empty. Please enter all fields.");
        
        $username = filter($_POST["username"]);
        $password = filter($_POST["password"]);
        $confirmation = filter($_POST["confirmation"]);
        $email = filter($_POST["email"]);
        
        if ($password != $confirmation)
            apologize("Passwords do not match.");
        
        if (!filter_var($email, FILTER_VALIDATE_EMAIL))
            apologize("Please enter a valid email address");
        
        $user_query = query("SELECT * from `users` WHERE `username` = ?", $username);
        $email_query = query("SELECT * from `users` WHERE `email` = ?", $email);
        
        $user_query = array_filter($user_query); 
        $email_query = array_filter($email_query);
            
        if (!empty($user_query))
            apologize("Username already exists");
            
        if (!empty($email_query))
            apologize("Email ID already exists");
            
        // from this point onwards, we're ready to log details to the database
        query("INSERT INTO `users` (`username`, `hash`, `cash`, `email`) VALUES(?, ?, ?, ?)", $username, crypt($password), 10000.0000, $email);
        
        // log in the user and redirect
        $_SESSION["id"] = query("SELECT LAST_INSERT_ID() AS id")[0]["id"];
        redirect("index.php");
    }
?>
