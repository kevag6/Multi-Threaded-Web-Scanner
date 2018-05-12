# Multi-Threaded-Web-Scanner
GUI application that scans a list of URLs for a specific list of words


Basic GUI web scanner that asks user for two files:

The first file being a list of valid URLs. The GUI app uses wxURL to open each URL and retrieve all the HTML content associated with the URL and its pages.

The second file is a list of words that will be used to search each web page (URL).

Once all threads have completed their assigned searches, a new text file is displayed showing the count of each word found in each URL. 

