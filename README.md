# Oanda rates streamer

Stream rates from [Oanda](http://www.oanda.com/) and store them in a database.

## Setup

As of march 2016, you will need two things, a `TOKEN` and `ACCOUNT_ID`.

#### `TOKEN`

- Create a practice account on [oanda](https://www.oanda.com).
- Go to `Manage API Access` and reqest a token.

#### `ACCOUNT_ID`

```
$ curl -H "Authorization: Bearer TOKEN" https://api-fxpractice.oanda.com/v1/accounts
```

Should returns something like:

```json
{
  "accounts": [
    {
      "accountsId": 1234567,
      "accountName": "Primary",
      "accountCurrency": "EUR",
      "marginRate": 0.02
    }
  ]
}
```

#### Test if is everything is working

```
$ curl -H "Authorization: Bearer TOKEN" "https://stream-fxpractice.oanda.com/v1/prices?accountId=ACCOUNT_ID&instruments=EUR_USD"
```

To query several pairs, separate them with `%2C`. e.g: `EUR_USD%2CUSD_CAD`.

You should see something like:

```json
{"tick":{"instrument":"AUD_CAD","time":"2016-03-02T14:14:07.132386Z","bid":0.97279,"ask":0.97306}}
{"tick":{"instrument":"AUD_CAD","time":"2016-03-02T14:14:08.097863Z","bid":0.97282,"ask":0.97306}}
{"heartbeat":{"time":"2016-03-02T14:14:09.840512Z"}}
{"tick":{"instrument":"AUD_CAD","time":"2016-03-02T14:14:10.323880Z","bid":0.97281,"ask":0.97308}}
{"tick":{"instrument":"AUD_CAD","time":"2016-03-02T14:14:10.419219Z","bid":0.97282,"ask":0.97308}}
...
```

## Dependencies

- [libcurl](https://curl.haxx.se/libcurl/c/)
- [sqlite3](https://www.sqlite.org/index.html)
- [json-parser](https://github.com/udp/json-parser) (shipped with the project)

## Installation

```
$ mkdir build
$ cd build
$ cmake ..
```

## CLI Usage

```
$ cd build/cli
$ make
$ ./stream -a 72383119 -t 9f86d081884c7d659a2feaa0c55ad015 -i EUR_USD -d DB.sql
```

The flags are:
- `a` account id,
- `t` oanda token.
- `i` instruments, space separated e.g `EUR_USD EUR_CHF`.
- `d` database name (default is `stream.sql`)

## License

MIT, see [LICENSE.md](https://github.com/vaalentin/oanda-stream/blob/master/LICENSE.md) for more details.
