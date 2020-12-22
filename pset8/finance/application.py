import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Make table if not exist
db_finance = db.execute(
    "CREATE TABLE if not EXISTS finance(finance_id INTEGER NOT NULL, symbol TEXT NOT NULL, name TEXT NOT NULL, qtd NUMERIC NOT NULL, price DECIMAL(5,2) NOT NULL, total_cost DECIMAL(7,2) NOT NULL);")
db_history = db.execute("CREATE TABLE if not EXISTS history (history_id INTEGER NOT NULL, symbol TEXT NOT NULL, shares TEXT NOT NULL, price DECIMAL(5,2) NOT NULL, date_time TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP, action TEXT NOT NULL);")
# db_excl = db.execute("DROP TABLE history")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    range_size = db.execute("SELECT COUNT(*) as count FROM finance WHERE finance_id = :finance_id",
                            finance_id=session["user_id"])
    size = range_size[0]['count']
    get_data = db.execute("SELECT * FROM finance WHERE finance_id = :finance_id ORDER BY symbol, name",
                          finance_id=session["user_id"])
    get_sum = db.execute("SELECT SUM(total_cost) as total_cost FROM finance WHERE finance_id = :finance_id",
                         finance_id=session["user_id"])
    get_cash = db.execute("SELECT cash FROM users WHERE id = :ID", ID=session["user_id"])
    cash_id = get_cash[0]['cash']
    total_sum = get_sum[0]['total_cost']
    try:
        total_cash = total_sum + cash_id
    except:
        total_cash = cash_id
    cash_dol = usd(cash_id)
    total_dol = usd(total_cash)

    symblist = []
    namelist = []
    sharlist = []
    pricelist = []
    totlist = []

    for i in range(0, size):
        symblist.append(get_data[i]['symbol'])
        namelist.append(get_data[i]['name'])
        sharlist.append(get_data[i]['qtd'])
        pricelist.append(usd(float(get_data[i]['price'])))
        totlist.append(usd(float(get_data[i]['total_cost'])))

    for s in symblist:
        quote = lookup(s)
        update_price = db.execute("UPDATE finance SET price = :price WHERE symbol = :symbol",
                                  price=quote["price"], symbol=s)
        get_priceandqtd = db.execute("SELECT price, qtd FROM finance WHERE finance_id = :finance_id AND symbol = :symbol",
                                     finance_id=session["user_id"], symbol=s)
        get_price = get_priceandqtd[0]["price"]
        get_qtd = get_priceandqtd[0]["qtd"]
        total_cost = get_price * get_qtd
        update_totalcost = db.execute(
            "UPDATE finance SET total_cost = :total_cost WHERE symbol = :symbol", total_cost=total_cost, symbol=s)

    return render_template("index.html", symbol=symblist, name=namelist, shares=sharlist, price=pricelist, total=totlist, size=size, cash=cash_dol, total_cash=total_dol)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Quantity required by the buyer
        src = request.form.get("symbol")
        qtd = int(request.form.get("quantity"))

        id_session = session["user_id"]

        # Get dates IEX

        quote = lookup(src)
        name = quote["name"]
        symbol = quote["symbol"]
        price = quote["price"]

        # Get cash quantity in DB
        dbcash = db.execute("SELECT cash FROM users WHERE id = :id_session",
                            id_session=id_session)
        cash = dbcash[0]['cash']

        # Charge
        price_charged = price * qtd
        if cash < price_charged:
            return apology("CAN'T AFFORD", 400)
        change_dbcash = db.execute("UPDATE users SET cash = cash - :price_charged WHERE id = :id_session",
                                   price_charged=price_charged, id_session=id_session)

        result = db.execute("SELECT qtd FROM finance WHERE finance_id = :id_session AND symbol = :symbol",
                            id_session=id_session, symbol=symbol)

        if not result:
            insert_finance = db.execute("INSERT INTO finance(finance_id, symbol, name, qtd, price, total_cost) VALUES(:id_session, :symbol, :name, :qtd, :price, :price_charged)",
                                        id_session=id_session, symbol=symbol, name=name, qtd=qtd, price=price, price_charged=price_charged)
        else:
            update_finance = db.execute("UPDATE finance SET qtd = qtd + :qtd, total_cost = total_cost + :price_charged WHERE symbol = :symbol AND finance_id = :id_session",
                                        qtd=qtd, price_charged=price_charged, symbol=symbol, id_session=id_session)

        action = "buy"
        buy_history = db.execute("INSERT INTO history(history_id, symbol, shares, price, action) VALUES(:history_id, :symbol, :shares, :price, :action)",
                                 history_id=id_session, symbol=symbol, shares=qtd, price=price, action=action)
        flash('Bought!')
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    id_session = session["user_id"]

    range_size = db.execute("SELECT COUNT(*) as count FROM history WHERE history_id = :id_session",
                            id_session=id_session)
    size = range_size[0]['count']

    db_history = db.execute("SELECT * FROM history WHERE history_id = :id_session ORDER BY date_time",
                            id_session=id_session)

    symblist = []
    sharlist = []
    pricelist = []
    translist = []

    for i in range(0, size):
        symblist.append(db_history[i]["symbol"])
        sharlist.append(db_history[i]["shares"])
        pricelist.append(usd(db_history[i]["price"]))
        translist.append(db_history[i]["date_time"])

    return render_template("history.html", symbol=symblist, shares=sharlist, price=pricelist, transacted=translist, size=size)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        src = request.form.get("symbol")
        quote = lookup(src)
        try:
            return render_template("symbol.html", name=quote["name"], symbol=quote["symbol"], price=usd(quote["price"]))
        except:
            return apology("Invalid symbol", 404)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        user = request.form.get("username")
        password = request.form.get("password")
        passwordagain = request.form.get("passwordagain")

        # Ensure password not equals password
        if password != passwordagain:
            return apology("password not equals", 404)

        passhash = generate_password_hash(password)

        # Ensure username was submitted
        if not user:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 403)

        else:
            db.execute("INSERT INTO users(username, hash) VALUES(:username, :password)", username=user, password=passhash)

            # Query database for username
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                              username=request.form.get("username"))

            # Ensure username exists and password is correct
            if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
                return apology("invalid username and/or password", 403)

            # Remember which user has logged in
            session["user_id"] = rows[0]["id"]
            flash('Registered!')
            return redirect("/")

    return render_template("/register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    id_session = session["user_id"]
    # Getting data
    range_size = db.execute("SELECT COUNT(*) as count FROM finance WHERE finance_id = :finance_id", finance_id=id_session)
    size = range_size[0]['count']
    get_data = db.execute("SELECT * FROM finance WHERE finance_id = :finance_id ORDER BY symbol", finance_id=id_session)
    get_symb = []

    for i in range(0, size):
        get_symb.append(get_data[i]['symbol'])

    if request.method == "POST":
        symb_form = request.form.get("symbol")

        # QTD
        shares = int(request.form.get("quantity"))
        get_qtd = db.execute("SELECT qtd FROM finance WHERE symbol = :symbol AND finance_id = :id_session ",
                             symbol=symb_form, id_session=id_session)
        qtd = get_qtd[0]["qtd"]

        if not symb_form:
            return apology("missing symbol", 400)
        if not shares:
            return apology("missing shares", 400)

        if shares > qtd:
            return apology("too many shares", 400)
        # PRICE
        get_price = db.execute("SELECT price FROM finance WHERE symbol = :symbol AND finance_id = :id_session ",
                               symbol=symb_form, id_session=id_session)
        price = get_price[0]["price"]
        price_charged = price * shares
        # UPDATE data
        update_sell = db.execute("UPDATE finance SET qtd = qtd - :qtd, total_cost = total_cost - :price_charged WHERE symbol = :symbol AND finance_id = :id_session",
                                 qtd=shares, price_charged=price_charged, symbol=symb_form, id_session=id_session)
        update_cash = db.execute("UPDATE users SET cash = cash + :price_charged WHERE id = :id_session",
                                 price_charged=price_charged, id_session=id_session)
        delete_sell = db.execute("DELETE FROM finance WHERE qtd = 0")

        sharesneg = f"-{shares}"
        action = "sold"
        buy_history = db.execute("INSERT INTO history(history_id, symbol, shares, price, action) VALUES(:history_id, :symbol, :shares, :price, :action)",
                                 history_id=id_session, symbol=symb_form, shares=sharesneg, price=price, action=action)

        flash('Sold!')
        return redirect("/")
    return render_template("/sell.html", size=size, symbol=get_symb)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
