# OLM Unit Tests

## Install dependencies

- Requires python3 and pip
- `$ pip install -r requirements.txt`

## Run Unit Tests

- Make a vcan0 bus
  - `$ sudo ./../scripts/vcan.sh`
- Run setup script (it will add files to the OLM caches needed for tests)
  - `$ sudo python setup_pytest.py`
- In one terminal: Build and start OLM
  - `$ cd ../build`
  - `$ cmake -DBOARD=generic ..`
  - `$ make`
  - `$ sudo ./oresat-linux-manager vcan0 -v`
- In another terminal: Run pytest
  - `$ sudo pytest .`
