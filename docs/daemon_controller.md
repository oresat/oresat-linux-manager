## App/Daemon list and controller OD entries
### App/Daemon list OD entry
| Sub Index | Usage                         | Data Type   | Access   |
| :-------- | :---------------------------: | :---------: | :------: |
|     0     | Number of subindex in record  | uint8       | readonly |
|     1     | App name 1                    | DOMAIN      | readonly |
|    ...    | ...                           | DOMAIN      | readonly |
|    127    | App name 127                  | DOMAIN      | readonly |

- This OD is list of app names where the index can be used by App/Daemon controller OD to controll that App/Daemon.
- An app that call app_register() will be added the app list.

### App/Daemon controller OD entry
| Sub Index | Usage                             | Data Type | Access    |
| :-------- | :-------------------------------: | :-------: | :-------: |
|     0     | Number of subindex in record      | uint8     | readonly  |
|     1     | Current index in app list array   | uint8     | readwrite |
|     2     | App name                          | DOMAIN    | readonly  |
|     3     | App current state                 | int32     | readonly  |
|     4     | App change state                  | int32     | readwrite |
|     5     | Daemon service name               | DOMAIN    | readonly  |
|     6     | Daemon current state              | int32     | readonly  |
|     7     | Daemon change state               | int32     | readwrite |

### How App contoller OD entries work:
- Master node can set subindex 1 (app list index) with the index of the app wanted form the app list. Updating that index will load all other subidexes with the that app info.
- App contoller
    - subindex 2: App's name.
    - subindex 3: App current state 0 running, 1 for stopped, 2 for error.
    - subindex 4: Change app's state 0 start/restart, 1 for stop.
- Daemon controller
    - subindex 5: Daemon service name.
    - subindex 6: Daemon current state 0 running, 1 for stopped, 2 for error.
    - subindex 7: Change daemon's state 0 start/restart, 1 for stop.
