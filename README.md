# Advanced-programming

Anomalies detection of flight data parameters.

Starting with normal flying features, learn them (like threshold, etc), then run a dummy flight and check for anomalies in real-time.

In addition, the project contains communication with the client, with a Command Pattern design pattern, that gives the client those options (it looks like that):

Welcome to the Anomaly Detection Server.
Please choose an option:
1. upload a time series CSV file
2. algorithm settings
3. detect anomalies
4. display results
5. upload anomalies and analyze results
6. exit

[Meaning:

1. Upload file to train normal flying parameters for each feature
2. Change correlation threshold
3. Time step + description of who's features weren't in normal correlation
4. Show anomalies with a range of time steps, like that:

4,7

120, 170

1702, 1703

Done
  
  (meaning that from 4 - 7 there were anomalies, etc)
  
5. Upload anomalies file, and show True positive and False positive rates.
6. Yes, well, that... XD
]
