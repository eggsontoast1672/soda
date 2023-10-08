import dataclasses


@dataclasses.dataclass
class SodaError(Exception):
    message: str
