# Custom class hijacks for PTPy
import ptpy
from construct import Container

def custom_recv(self, code, param = []):
    ptp = Container(
        OperationCode=code,
        SessionID=self._session,
        TransactionID=self._transaction,
        Parameter=param
    )

    response = self.recv(ptp)
    return response

def custom_send(self, code, data, param = []):
    ptp = Container(
        OperationCode=code,
        SessionID=self._session,
        TransactionID=self._transaction,
        Parameter=param
    )

    response = self.send(ptp, data)
    return response

def custom_mesg(self, code, param = []):
    ptp = Container(
        OperationCode=code,
        SessionID=self._session,
        TransactionID=self._transaction,
        Parameter=param
    )

    response = self.mesg(ptp)
    return response

def setup():
	setattr(ptpy.PTP, "custom_recv", custom_recv)
	setattr(ptpy.PTP, "custom_send", custom_send)
	setattr(ptpy.PTP, "custom_mesg", custom_mesg)
