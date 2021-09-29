# Advanced-programming

Anomalies detection (about fly simulator)

Starting with normal flying features, learn them (like threshold etc), then run a test "fly" and check for anomalies at real time.

In addition, the project contain a communication with client, with Command Pattern design pattern, that give the client those options (it look like that):

Welcome to the Anomaly Detection Server.
Please choose an option:
1. upload a time series csv file
2. algorithm settings
3. detect anomalies
4. display results
5. upload anomalies and analyze results
6. exit

[Meaning:

1. upload file to train normal flying parameters for each feature
2. change correletion threshold
3. time step + description of who's features wasnt in normal correletion
4. show anomalies with range of time steps, like that:

4,7
120, 170
1702, 1703
Done
  
  meaning that from 4 - 7 there were anomalies, etc
  
5. Upload anomalies file, and show True positive and False positive rate.
6. ye, that... XD
]
